// system
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
// stdlib
#include <cerrno>
#include <cstring>
#include <iostream>
// project
#include "src/utils/utils.h"

/**
 * @brief Processes buffer message I/O
 * 
 * @param sockfd is the socket file descriptor
 * @param payload is the query message
 * @return exit code
 */
ssize_t query(int sockfd, const char *payload) {
  // Payload length
  uint32_t len = (uint32_t)std::strlen(payload);
  // Check for message size overflow
  if (len > BUFFER_SIZE) {
    return -1;
  }
  char wbuf[4 + BUFFER_SIZE];
  // Copy payload size and message to buffer
  memcpy(wbuf, &len, 4);
  memcpy(&wbuf[4], payload, len);
  int32_t retval = send_full(sockfd, wbuf, 4 + len);
  if (retval) {
    return retval;
  }
  // Initialize receive buffer memory allocation
  char rbuf[4 + BUFFER_SIZE];
  errno = 0;
  retval = recv_full(sockfd, rbuf, 4);
  // Check if EOF or receive error
  if (retval) {
    msg(EXIT_FAILURE, errno == 0 ? "EOF" : "Receive");
    return retval;
  }
  memcpy(&len, rbuf, 4);
  // Check for message size overflow
  if (len > BUFFER_SIZE) {
    msg(EXIT_FAILURE, "Overflow");
    return -1;
  }
  retval = recv_full(sockfd, &rbuf[4], len);
  if (retval) {
    msg(EXIT_FAILURE, "Receive");
    return retval;
  }
  std::cout << "Server: " << &rbuf[4] << std::endl;
  return 0;
}

int main() {
  int sockfd; // Socket handle for TCP connection
  ssize_t retval; // Return value

  // Socket handle
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // Check if socket handle has been returned successfully
  if (sockfd == -1)
    msg(EXIT_FAILURE, "Socket");

  // Initialize server socket endpoint scheme
  struct sockaddr_in cli_addr = {
    .sin_family = AF_INET, // IPv4 address scheme
    .sin_port = htons(6379), // Default Redis data store port 6379
    .sin_addr = {
      .s_addr = htonl(INADDR_LOOPBACK) // Localhost 127.0.0.1
    },
    .sin_zero = {} // Byte padding for struct memory alignment
  };

  // Connect socket
  retval = connect(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
  // Check if socket has been connected successfully
  if (retval == -1)
    msg(EXIT_FAILURE, "Connect");
  
  // Query request

  retval = query(sockfd, "Hello");
  if (retval)
    msg(EXIT_FAILURE, "Query");
  
  /**
   * @brief Manual buffer read and write testing
   */

  // // Write buffer
  // char wbuf[] = "hello";
  // // Send buffer data
  // retval = send(sockfd, wbuf, std::strlen(wbuf), 0);
  // // Check if buffer msg has been sent
  // if (retval == -1)
  //   msg(EXIT_FAILURE, "Send");
  
  // // Read buffer
  // char rbuf[64] = {};
  // // Receive buffer data
  // retval = recv(sockfd, rbuf, sizeof(rbuf) - 1, 0);
  // // Check if buffer msg has been received
  // if (retval == -1)
  //   msg(EXIT_FAILURE, "Receive");
  
  // std::cout << "Server: " << rbuf << std::endl;

  close(sockfd);
}

