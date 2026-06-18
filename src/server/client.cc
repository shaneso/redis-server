// system
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
// stdlib
#include <cerrno>
#include <cstring>
#include <iostream>
// project
#include "src/util/logging.h"

int main() {
  int sockfd; // Socket handle for TCP connection
  ssize_t retval; // Return value

  // Socket handle
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // Check if socket handle has been returned successfully
  if (sockfd == -1)
    err(EXIT_FAILURE, "Socket");

  // Initialize server socket endpoint scheme
  struct sockaddr_in cli_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(6379),
    .sin_addr = {
      .s_addr = htonl(INADDR_LOOPBACK) // Localhost 127.0.0.1
    },
    .sin_zero = {}
  };

  // Connect socket
  retval = connect(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
  // Check if socket has been connected successfully
  if (retval == -1)
    err(EXIT_FAILURE, "Connect");

  // Write buffer
  char wbuf[] = "hello";
  // Send buffer data
  retval = send(sockfd, wbuf, std::strlen(wbuf), 0);
  // Check if buffer msg has been sent
  if (retval == -1)
    err(EXIT_FAILURE, "Send");
  
  // Read buffer
  char rbuf[64] = {};
  // Receive buffer data
  retval = recv(sockfd, rbuf, sizeof(rbuf) - 1, 0);
  // Check if buffer msg has been received
  if (retval == -1)
    err(EXIT_FAILURE, "Receive");
  
  std::cout << "Server: " << rbuf << std::endl;

  close(sockfd);
}

