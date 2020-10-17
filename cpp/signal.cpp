#include "signal.h"

#include <fstream>
#include <unistd.h>

std::vector<std::pair<bool, unsigned>> loadValsAndTimes(const std::string& file_path) {
  std::ifstream in_file(file_path);
  std::string line;

  std::vector<std::pair<bool, unsigned>>  vals_and_times;

  while (std::getline(in_file, line)) {
    const bool state = line[0] == '1';
    const unsigned time = std::atof(line.substr(2).c_str());

    vals_and_times.emplace_back(state, time);
  }

  return vals_and_times;
}


Signal::Signal(const std::string& file_path) : signal_val_and_time_(loadValsAndTimes(file_path)) {}

void Signal::emitSignal() {
  for (const std::pair<bool, unsigned>& val_and_time : signal_val_and_time_) {
    // Opposite of what was read.
    emitter_.setState(!val_and_time.first);
    usleep(val_and_time.second);
  }

  emitter_.turnOff();
}
