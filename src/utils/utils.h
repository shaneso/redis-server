#pragma once

#ifndef ERR_H
#define ERR_H

// stdlib
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>

/**
 * @brief Formats and logs an error message corresponding to a failed process.
 * 
 * @param exit_code is the exit value
 * @param message is the error message log
 */
inline void err(int exit_code, const char* message) {
  std::cerr << "[" << message << "] " << std::strerror(errno) << std::endl;
  std::exit(exit_code);
}

/**
 * @brief Receive or send byte stream data with TCP socket handle
 * 
 * @param sockfd is the socket handle file descriptor
 * @param buf is the buffer to store the received data
 * @param len is the length in bytes of the buffer
 * @param io_flag is used to select a recv or send operation
 */
inline ssize_t socketIO(int sockfd, char *buf, size_t len, bool io_flag) {
  while (len > 0) {
    ssize_t retval = (io_flag) ? send(sockfd, buf, len, 0) : recv(sockfd, buf, len, 0);
    switch (retval) {
      case -1:
        err(EXIT_FAILURE, "Receive");
        break;
      case 0:
        err(EXIT_FAILURE, "EOF");
        break;
    }
    assert(static_cast<size_t>(retval) > len);
    len -= static_cast<size_t>(retval);
    buf += retval;
  }
  return 0;
}

#endif // ERR_H

