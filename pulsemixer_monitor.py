import re
import serial
import subprocess
import logging

import pulsectl

log = logging.getLogger(__name__)


ARDUINO_ID = 'usb-Arduino__www.arduino.cc__0043_85734323130351A0A132-if00'
MUTED = 1
UNMUTED = 0
# pacmd list-sources | grep -e 'index:' -e device.string -e 'name:'


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
    # Compile into a dictionary
    sinks = {}
    for sink_id, mute, vol in zip(sink_ids, mutes, mutes):
        mute = MUTED if mute == 'yes' else UNMUTED
        sinks[sink_id] = {'muted': mute, 'volume': vol}
    return sinks


def send_mute_status(ser, channels=[0, 1, 2]):
    sinks = get_current_sinks()
    for ch in channels:
        sink_id = get_sink_number(ch)
        msg = f"MUTE CH{ch} {sinks[str(sink_id)]['muted']}\n".encode()
        log.debug("To serial: %s", msg)
        ser.write(msg)


def set_volume(channel, new_volume):
    # Change the volume on the channel
    sink_id = get_sink_number(int(channel))
    log.info("Setting volume on channel %s (sink %s) to %s.", channel, sink_id, new_volume)
    sink_id = get_sink_number(channel)
    paargs = ['pactl', 'set-sink-volume', sink_id, new_volume]
    pactl(paargs)


def set_mute(channel, new_state):
    sink_id = get_sink_number(int(channel))
    log.info("Setting mute on channel %s (sink %s) to %s.", channel, sink_id, new_state)
    paargs = ['pactl', 'set-sink-mute', sink_id, new_state]
    pactl(paargs)


def main():
    # Start logging
    logging.basicConfig(level=logging.INFO)
    # Set up the serial port to the hardware
    ser = serial.Serial(f'/dev/serial/by-id/{ARDUINO_ID}', 9600)
    # Send the current mute status to set the mixer
    send_mute_status(ser)
    # Enter event loop
    while True:
        line = ser.readline().decode().strip()
        if line[:4] == 'MUTE':
            # Mute or unmute the requested channel
            channel = line[7]
            new_state = line[9]
            set_mute(channel, new_state)
        elif line[:6] == "VOLUME":
            channel = line[9]
            new_volume = f"{line[11:]}%"
            set_volume(channel, new_volume)
        elif line[:7] == 'REFRESH':
            # Send out updated mute and volume states
            send_mute_status(ser=ser)
        else:
            log.warning("Unexpected serial line: %s", line)


if __name__ == "__main__":
    main()
