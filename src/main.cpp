#include "../include/Editor.hpp"
#include <curses.h>
#include <iostream>

typedef struct Args {
  std::string filename;
} Args;

int HandleArgs(Args *args, int argc, char **argv) {
  if (argc <= 1) {
    std::fprintf(stderr, "Error: No file was provided.\n");
    return -1;
  }
  args->filename = std::string(argv[1]);
  return 0;
}

int main(int argc, char **argv) {
  Args args;
  if (HandleArgs(&args, argc, argv) != 0) {
    return -1;
  }
  try {
    Editor e(Editor(std::string(args.filename)));
    e.Run();
  } catch (...) {
    // TODO: fix error handling
    std::cerr << "An error occured.\n";
    return 1;
  }
  return 0;
}
