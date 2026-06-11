#include <iostream>
#include <cstring>
#include <cstdint>
#include <cerrno>
#include <sys/socket.h>
#include <stdexcept>

int main() {

  int error_number = 0;

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  int value = 1;

  try {
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == -1) {
      error_number = errno;
      throw std::runtime_error("Error: Socket options failed to set.");
    }
  }
  catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << "Log: " << std::strerror(error_number) << std::endl;
  }

  return 0;
}

