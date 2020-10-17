#include <wiringPi.h>

IRDevice::IRDevice(const int pin_num, const int mode) : pin_num_(pin_num) {
  if (!gpio_setup_done_) {
    wiringPiSetup();
    gpio_setup_done_ = true;
  }
  pinMode(pin_num, mode)
}


Receiver::Receiver() : IRDevice(17, INPUT) {}

bool Receiver::read() {
  return digitalRead(pinNum()) == HIGH;
}

Emitter::Emitter() : IRDEvice(23, OUTPUT) {}

void Emitter::setState(bool on) {
  digitalWrite(pinNum(), (on ? HIGH : LOW));
  on_ = on;
}
