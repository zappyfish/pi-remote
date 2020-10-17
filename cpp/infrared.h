#pragma once

class IRDevice {

  IRDevice(const int pin_num, const int mode);
  ~IRDevice() = default;

private:
  static bool gpio_setup_done_= false;
  const int pin_num_;

protected:
  int pinNum() { return pin_num_; }
};

class Receiver : public IRDevice {
public:
  Receiver();
  ~Receiver() = default;

  bool read();

  unsigned millisecondsUntilChange();
};

class Emitter : public IRDevice {

public:
  Emitter();
  ~Emitter() = default;

  void turnOn() { setState(true); }
  void turnOff() { setState(false); }

  bool switchState() { setState(!on_); }

  bool isOn() { return on_; }

private:
  bool on_;

  void setState(const bool on);
};
