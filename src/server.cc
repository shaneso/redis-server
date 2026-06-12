#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>

int main() {

  // Create socket handle (file descriptor)

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  int opt_value = 1;

  int error_number = 0;

  // Set socket options

  try {
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_value, sizeof(opt_value)) == -1) {
      error_number = errno;
      throw std::runtime_error("Error: Socket options failed to set.");
    }
  }
  catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << "Log: " << std::strerror(error_number) << std::endl;
  }

  // Bind selected IP address and port to socket

  struct sockaddr_in addr = {
    .sin_family = AF_INET, // IPv4 address scheme
    .sin_port = htons(6379), // Default Redis data store port 6379
    .sin_addr = {
      .s_addr = htonl((127 << 24) | (0 << 16) | (0 << 8) | 1) // Localhost 127.0.0.1
    },
    .sin_zero = {}
  };

  return 0;

}

