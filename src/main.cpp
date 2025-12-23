#include "../include/Editor.hpp"
#include <iostream>

struct Args {
  std::string filename;
};

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
    Editor e(std::string(args.filename));
    e.Run();
  } catch (const std::exception &ex) {
    std::cerr << "An exception occured: " << ex.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "An unknown error occured.\n";
    return 1;
  }
  return 0;
}
