from datetime import datetime
import sys
import RPi.GPIO as GPIO

RECEIVER = 17

def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(RECEIVER, GPIO.IN)


def get_reading():
    return GPIO.input(RECEIVER)


def wait_for_change(start_state):
    start_time = datetime.now()
    while start_state == get_reading():
        pass
    return (datetime.now() - start_time).total_seconds()


def should_stop_recording(start_datetime, max_recording_time_s):
    time_recording = datetime.now() - start_datetime
    return time_recording.total_seconds() > max_recording_time_s


def main(recording_time_s, output_file):
    start_datetime = datetime.now()
    with open(output_file, 'w') as f:
        current_state = get_reading()
        while not should_stop_recording(start_datetime, recording_time_s):
            time_between_change_us = wait_for_change(current_state)
            # Write a line to file indicating the last state (1 or 0) and time in that stat
            f.write("{},{}\n".format(current_state, time_between_change_us))
            current_state = get_reading()


if __name__ == '__main__':
    _, recording_time_s, output_file = sys.argv
    setup()
    main(int(recording_time_s), output_file)
