#pragma once

#ifndef UTILS_H
#define UTILS_H

// stdlib
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>

// Maximum buffer message byte size
#define BUF_MSG_MAX 4096

/**
 * @brief Formats and logs a status message corresponding to a process.
 * 
 * @param exit_code is the exit value
 * @param message is the displayed status message log
 */
inline void msg(int exit_code, const char* message) {
  std::cerr << "[" << message << "] " << std::strerror(errno) << std::endl;
  std::exit(exit_code);
}

/**
 * @brief Receive or send byte stream data with TCP socket handle
 * 
 * @param sockfd is the socket handle file descriptor
 * @param buf is the buffer to store the received data
 * @param len is the length in bytes of the buffer
 */
inline ssize_t recv_full(int sockfd, char *buf, size_t len) {
  while (len > 0) {
    ssize_t retval = recv(sockfd, buf, len, 0);
    // Return error or EOF code
    if (retval <= 0) {
      return -1;
    }
    assert(static_cast<size_t>(retval) <= len);
    len -= static_cast<size_t>(retval);
    buf += retval;
  }
  return 0;
}

/**
 * @brief Send byte stream data with TCP socket handle
 * 
 * @param sockfd is the socket handle file descriptor
 * @param buf is the buffer to store the received data
 * @param len is the length in bytes of the buffer
 */
inline ssize_t send_full(int sockfd, char *buf, size_t len) {
  while (len > 0) {
    ssize_t retval = send(sockfd, buf, len, 0);
    // Return error or EOF code
    if (retval <= 0) {
      return -1;
    }
    assert(static_cast<size_t>(retval) <= len);
    len -= static_cast<size_t>(retval);
    buf += retval;
  }
  return 0;
}

#endif // UTILS_H

