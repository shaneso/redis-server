#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "err.h"

/**
 * @brief Formats and logs an error message corresponding to a failed process.
 * 
 * @param exit_code is the exit value
 * @param message is the error message log
 */
void err(int exit_code, const char* message) {
  std::cerr << "[" << message << "] " << std::strerror(errno) << std::endl;
  std::exit(exit_code);
}

