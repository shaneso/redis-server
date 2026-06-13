#include <arpa/inet.h>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>

#define BACKLOG SOMAXCONN // Socket max connections (/proc/sys/net)

/**
 * @brief Formats and logs an error message corresponding to a failed process.
 * 
 * @param exit_code is the exit value
 * @param message is the error message log
 */
void err(int exit_code, const char* message) {
  std::cerr << message << ": " << std::strerror(errno) << std::endl;
  std::exit(exit_code);
}

int main() {

  // Socket handle and return value

  int sockfd, retval;

  // Create socket handle (fd)

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // Check socket handle status

  if (sockfd == -1)
    err(EXIT_FAILURE, "Socket");

  int opt_value = 1; // Set socket option value param

  // Set socket options

  retval = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_value, sizeof(opt_value));

  // Check if socket options have been set

  if (retval == -1)
    err(EXIT_FAILURE, "Socket option");

  // Initialize socket address config

  struct sockaddr_in addr = {
    .sin_family = AF_INET, // IPv4 address scheme
    .sin_port = htons(6379), // Default Redis data store port 6379
    .sin_addr = {
      .s_addr = htonl((127 << 24) | (0 << 16) | (0 << 8) | 1) // Localhost 127.0.0.1
    },
    .sin_zero = {} // Byte padding for struct memory alignment
  };

  // Bind selected IP address and port to socket

  retval = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));

  // Check bind status

  if (retval == -1)
    err(EXIT_FAILURE, "Bind");
  
  // Listen for connections on a socket

  retval = listen(sockfd, BACKLOG);

  // Check if socket is established as passive

  if (retval == -1)
    err(EXIT_FAILURE, "Listen");

  return EXIT_SUCCESS;

}

