#pragma once

#include <string>
#include "infrared.h"

class Recorder {

public:

Recorder() = default;
~Recorder() = default;

void record(const unsigned duration_seconds, const std::string& output_path);

private:
  Receiver receiver_;
};
