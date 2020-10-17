#include <wiringPi.h>
#include "infrared.h"
#include <chrono>

void setupInterrupt() {
  const char[] command = "gpio edge 17 both";
  system(command);
}

IRDevice::IRDevice(const int pin_num, const int mode) : pin_num_(pin_num) {
  if (!gpio_setup_done_) {
    wiringPiSetup();
    gpio_setup_done_ = true;
  }
  pinMode(pin_num, mode)
}


Receiver::Receiver() : IRDevice(17, INPUT) {
  setupInterrupt();
}

bool Receiver::read() {
  return digitalRead(pinNum()) == HIGH;
}

unsigned Receiver::millisecondsUntilChange() {
  const auto start = std::chrono::high_resolution_clock::now();
  waitForInterrupt(pinNum(), -1);
  const auto elapsed = std::chrono::high_resolution_clock::now() - start;

  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

Emitter::Emitter() : IRDEvice(23, OUTPUT) {}

void Emitter::setState(bool on) {
  digitalWrite(pinNum(), (on ? HIGH : LOW));
  on_ = on;
}
