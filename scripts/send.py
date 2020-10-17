import RPi.GPIO as GPIO
from time import sleep
from datetime import datetime

EMITTER = 23


def flip(b):
    if b == 0:
        return 1
    else:
        return 0

class Signal:

    def __init__(self, fname):
        with open(fname, 'r') as f:
            data = [ln for ln in f.readlines()]
        self.start_output = flip(int(data[0][0]))
        self.times = [float(d.split(',')[1]) for d in data]

    def play_signal(self, output_fcn):
        current_output = self.start_output
        last_t = datetime.now()
        for t_s in self.times:
            output_fcn(current_output)
            print("desired elapsed: {} seconds".format(t_s))
            sleep(t_s)
            current_output = flip(current_output)
            t = datetime.now()
            actual = (t - last_t).total_seconds()
            print("actual elapsed: {} seconds".format(actual))
            print("diff: {} seconds".format(t_s - actual))
            print("------------")
            last_t = t


def get_path(signal_name):
    return "recordings/" + signal_name + ".txt"


def load_signals(signal_names):
    return {signal_name : Signal(get_path(signal_name)) for signal_name in signal_names}


def setup_output():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(EMITTER, GPIO.OUT)
    output_map = {0: GPIO.LOW, 1: GPIO.HIGH}
    return lambda x: GPIO.output(EMITTER, output_map[x])


def get_test_setup():
    names = ["on", "off"]
    return setup_output(), load_signals(names)


if __name__ == '__main__':
    f, signals = get_test_setup()
    signals['on'].play_signal(f)
