#include "signal.h"


int main(int argc, char *argv[]) {
  const std::string in_path = argv[1];

  Signal signal(in_path);
  signal.emitSignal();

  return 0;
}
