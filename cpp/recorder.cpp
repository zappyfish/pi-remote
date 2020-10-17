#include "recorder.h"
#include <fstream>
#include <chrono>

bool done(const std::chrono::steady_clock::time_point& begin, const unsigned duration_seconds) {
  std::chrono::steady_clock::time_point cur = std::chrono::steady_clock::now();
  const unsigned time_s = std::chrono::duration_cast<std::chrono::seconds>(cur - begin).count();

  return time_s > duration_seconds;
}

void writeLine(const bool state, const unsigned time_in_state_us, std::ofstream* outfile) {
  *outfile << (state ? "1" : "0") << "," << time_in_state_us << "\n";
}

void Recorder::record(const unsigned duration_seconds, const std::string& output_path) {
  std::ofstream outfile(output_path);
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  while (!done(begin, duration_seconds)) {
    const bool state = receiver_.read();
    const unsigned time_in_state_us = receiver_.millisecondsUntilChange();

    writeLine(state, time_in_state_us, &outfile);
  }

  outfile.close();
}
