#pragma once

#ifndef UTILS_H
#define UTILS_H

// stdlib
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>

// Maximum buffer message byte size
#define BUFFER_SIZE 131072

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
 * @brief Receive byte stream data with TCP socket handle
 * 
 * @param sockfd is the socket handle file descriptor
 * @param buf is the buffer to store the received data
 * @param len is the length in bytes of the buffer
 * @return number of bytes read or exit code
 */
inline ssize_t recv_full(int sockfd, char *buf, size_t len) {
  // Total number of bytes read from socket
  // size_t total = 0;
  while (len > 0) {
    ssize_t retval = recv(sockfd, buf, len, 0);
    // Check if EOF or error
    if (retval <= 0) return -1;
    assert((size_t)retval <= len);
    len -= (size_t)retval;
    // Move buffer pointer to the next available slot
    buf += (size_t)retval;
    // total += (size_t)retval;
  }
  // return (ssize_t)total;
  return 0;
}

/**
 * @brief Send byte stream data with TCP socket handle
 * 
 * @param sockfd is the socket handle file descriptor
 * @param buf is the buffer to store the received data
 * @param len is the length in bytes of the buffer
 * @return number of bytes read or exit code
 */
inline ssize_t send_full(int sockfd, char *buf, size_t len) {
  // Total number of bytes read from socket
  // size_t total = 0;
  while (len > 0) {
    ssize_t retval = send(sockfd, buf, len, 0);
    // Check if EOF or error
    if (retval <= 0) return -1;
    assert((size_t)retval <= len);
    len -= (size_t)retval;
    // Move buffer pointer to the next available slot
    buf += (size_t)retval;
    // total += (size_t)retval;
  }
  // return (ssize_t)total;
  return 0;
}

#endif // UTILS_H

