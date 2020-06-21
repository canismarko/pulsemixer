import serial
import subprocess
import logging

log = logging.getLogger(__name__)


ARDUINO_ID = 'usb-Arduino__www.arduino.cc__0043_85734323130351A0A132-if00'
# pacmd list-sources | grep -e 'index:' -e device.string -e 'name:'


def pactl(args):
    log.debug("Running pactl: %s.", args)
    subprocess.run(args)


def main():
    # Start logging
    logging.basicConfig(level=logging.DEBUG)
    # Set up the serial port to the hardware
    ser = serial.Serial(f'/dev/serial/by-id/{ARDUINO_ID}', 9600)
    while True:
        line = ser.readline().decode().strip()
        if line[:4] == 'MUTE':
            # Mute or unmute the requested channel
            channel = line[7]
            new_state = line[9]
            log.info("Setting mute on channel %s to %s.", channel, new_state)
            paargs = ['pactl', 'set-sink-mute', channel, new_state]
            pactl(paargs)
        elif line[:6] == "VOLUME":
            # Change the volume on the channel
            channel = line[9]
            new_volume = f"{line[11:]}%"
            log.info("Setting volume on channel %s to %s.", channel, new_volume)
            paargs = ['pactl', 'set-sink-volume', channel, new_volume]
            pactl(paargs)
        else:
            log.warning("Unexpected serial line: %s", line)


if __name__ == "__main__":
    main()
