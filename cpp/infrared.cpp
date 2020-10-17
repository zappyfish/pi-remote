#include <wiringPi.h>
#include "infrared.h"
#include <chrono>
#include <cstdlib>

bool IRDevice::gpio_setup_done_ = false;

IRDevice::IRDevice(const int pin_num, const int mode) : pin_num_(pin_num) {
  if (!gpio_setup_done_) {
    wiringPiSetup();
    gpio_setup_done_ = true;
  }
  pinMode(pin_num, mode);
}


Receiver::Receiver() : IRDevice(0, INPUT) {}

bool Receiver::read() {
  return digitalRead(pinNum()) == HIGH;
}

unsigned Receiver::millisecondsUntilChange() {
  const auto start = std::chrono::high_resolution_clock::now();

  const bool state = read();
  while (state == read());

  const auto elapsed = std::chrono::high_resolution_clock::now() - start;

  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

Emitter::Emitter() : IRDevice(4, OUTPUT), on_(false) {
  turnOff();
}

void Emitter::setState(bool on) {
  digitalWrite(pinNum(), (on ? HIGH : LOW));
  on_ = on;
}
