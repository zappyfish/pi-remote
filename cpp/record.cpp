#include "recorder.h"


int main(int argc, char *argv[]) {
  const unsigned recording_time_s = std::atoi(argv[1]);
  const std::string output_path = argv[2];

  Recorder recorder;
  recorder.record(recording_time_s, output_path);

  return 0;
}
