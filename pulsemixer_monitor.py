import re
import serial
import subprocess
import logging
import time

import pulsectl

log = logging.getLogger(__name__)


# ARDUINO_ID = 'usb-Arduino__www.arduino.cc__0043_85734323130351A0A132-if00'
ARDUINO_ID = "usb-FTDI_FT232R_USB_UART_AC012DYA-if00-port0"
MUTED = 1
UNMUTED = 0
# pacmd list-sources | grep -e 'index:' -e device.string -e 'name:'
SHORTNAMES = {
    'GP106 High Definition Audio Controller Digital Stereo (HDMI 2)': "HDMI",
    "Family 17h (Models 00h-0fh) HD Audio Controller Analog Stereo": "Speakers",
    "LifeChat LX-3000 Headset Analog Stereo": "Headset",
    "Simultaneous output to Family 17h (Models 00h-0fh) HD Audio Controller Analog Stereo, LifeChat LX-3000 Headset Analog Stereo, GP106 High Definition Audio Controller Digital Stereo (HDMI 2)": "Combined",
}


class Mixer():
    __shared_state = {}
    _serial = None
    def __init__(self):
        self.__dict__ = self.__shared_state
        # Establish a connection if one is required
        if self._serial is None:
            self._serial = serial.Serial(f'/dev/serial/by-id/{ARDUINO_ID}', 115200)

    def writeline(self, newline):
        if newline != "?set mute 0 0" or True:
            log.debug("Sending line to device: %s", newline)
            newline = f"{newline}\n"
            self._serial.write(newline.encode())
        else:
            log.debug("Ignoring line to device: %s", newline)

    def readline(self):
        return self._serial.readline().decode('ascii').strip()


def get_sink_number(channel):
    """Get the pulseaudio sink number for a given channel."""
    channels = [
        'combined',
        'alsa_output.usb-C-Media_Electronics_Inc._Microsoft_LifeChat_LX-3000-00.analog-stereo',
        'alsa_output.pci-0000_28_00.3.analog-stereo',
    ]
    ch_name = channels[int(channel)]
    process = subprocess.run(['pactl', 'list', 'short', 'sinks'], capture_output=True)
    response = process.stdout.decode()
    # Parse the pactl output for a device id
    match = re.search("^(\d+)\s+{}.*$".format(ch_name), response, flags=re.MULTILINE)
    if not match:
        raise RuntimeError("Sink '{}' not found in list:\n{}".format(ch_name, response))
    return match.group(1)


def pactl(args):
    log.debug("Running pactl: %s.", args)
    subprocess.run(args)


def get_current_sinks():
    # Get the full states of all pa sinks
    response = subprocess.run(['pactl', 'list', 'sinks'], capture_output=True).stdout.decode()
    sink_ids = re.findall("^Sink #(\d+)$", response, flags=re.MULTILINE)
    mutes = re.findall("^\s+Mute: (yes|no)$", response, flags=re.MULTILINE)
    volumes = re.findall("^\s+Volume: [-a-z]+: \d+ /\s+(\d+)%", response, flags=re.MULTILINE)
    device_names = re.findall('^\s+Description: (.*)$', response, flags=re.MULTILINE)
    # Compile into a dictionary
    sinks = {}
    for sink_id, mute, vol, name in zip(sink_ids, mutes, volumes, device_names):
        mute = MUTED if mute == 'yes' else UNMUTED
        sinks[int(sink_id)] = {'muted': mute, 'volume': vol, 'short_name': name}
    return sinks


def set_volume(channel, new_volume):
    # Change the volume on the channel
    sink_id = get_sink_number(int(channel))
    log.info("Setting volume on channel %s (sink %s) to %s.", channel, sink_id, new_volume)
    sink_id = get_sink_number(channel)
    paargs = ['pactl', 'set-sink-volume', sink_id, new_volume]
    pactl(paargs)


def set_mute(channel: int, new_state: bool):
    log.info("Setting mute on channel %d to %s.", channel, new_state)
    paargs = ['pactl', 'set-sink-mute', str(channel), "1" if new_state else "0"]
    pactl(paargs)


def set_volume(channel: int, new_volume: int):
    log.info("Setting volume on channel %d to %d.", channel, new_volume)
    paargs = ['pactl', 'set-sink-volume', str(channel), f"{new_volume}%"]
    pactl(paargs)    


def main():
    # Start logging
    logging.basicConfig(level=logging.WARNING)
    # Enter event loop
    mixer = Mixer()
    mixer.writeline("?RESET")
    while True:
        line = mixer.readline()
        handle_serial_line(line)
        # if line[:4] == 'MUTE':
        #     # Mute or unmute the requested channel
        #     channel = line[7]
        #     new_state = line[9]
        #     set_mute(channel, new_state)
        # elif line[:6] == "VOLUME":
        #     channel = line[9]
        #     new_volume = f"{line[11:]}%"
        #     set_volume(channel, new_volume)
        # elif line[:7] == 'REFRESH':
        #     # Send out updated mute and volume states
        #     send_mute_status(ser=ser)
        # else:
        #     log.warning("Unexpected serial line: %s", line)


def send_channel_names(n_channels):
    mixer = Mixer()
    sinks = get_current_sinks()
    names = [(sink_num, sink['short_name']) for sink_num, sink in sinks.items()]
    # Convert pre-defined names to 8-characters
    names = [(num, SHORTNAMES.get(n, n)) for num, n in names]
    # Convert to a space separated list of quoted strings
    names = ' '.join([f'"({id}, \'{name[:20]}\')"' for id, name in names])
    # Add extra empty strings for unused channels
    names += ''.join([' ""' for r in range(n_channels - len(sinks.values()))])
    line = f"CHANNELS SHORTNAMES {names}"
    mixer.writeline(line)


def send_channel_volumes():
    sinks = get_current_sinks()
    for id, props in sinks.items():
        send_channel_volume(id, props['volume'])


def send_channel_mutes():
    sinks = get_current_sinks()
    for id, props in sinks.items():
        send_channel_mute(id, props['muted'])


def send_channel_volume(channel_id, volume):
    mixer = Mixer()
    line = f"?set volume {channel_id} {volume}"
    mixer.writeline(line)
    time.sleep(0.1)


def send_channel_mute(channel_id, mute_state):
    mixer = Mixer()
    line = f"?set mute {channel_id} {mute_state}"
    mixer.writeline(line)
    time.sleep(0.1)


def handle_serial_line(line):
    # "REFRESH CHANNELS"
    if line.lower().startswith("!refresh channels"):
        log.debug("Received request to refresh channel names")
        n_channels = int(line.split(' ')[-1])
        send_channel_names(n_channels)
    elif line.lower().startswith("!refresh volumes"):
        log.debug("Received request to refresh volumes")
        send_channel_volumes()
    elif line.lower().startswith("!refresh mutes"):
        log.debug("Received request to refresh mute states")
        send_channel_mutes()        
    elif line.lower().startswith("!mute"):
        log.debug("Received request to mute channel")
        _, channel_id, status = line.split(' ')
        set_mute(channel=int(channel_id), new_state=bool(int(status)))
    elif line.lower().startswith("!set volume"):
        log.debug("Received volume change request")
        _, _, channel_id, new_vol = line.split(' ')
        set_volume(channel=int(channel_id), new_volume=int(new_vol))
    else:
        log.warning("Unexpected serial line: %s (%d chars)", line, len(line))

if __name__ == "__main__":
    main()
