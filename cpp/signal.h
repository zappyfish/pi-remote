#pragma once

#include "infrared.h"
#include <string>
#include <vector>

class Signal {

public:

  Signal(const std::string& file_path);
  ~Signal() = default;

  void emitSignal();

private:

  Emitter emitter_;
  const std::vector<std::pair<bool, unsigned>> signal_val_and_time_;

};
