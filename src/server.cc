#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>

int main() {

  // 

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

  return 0;

}

