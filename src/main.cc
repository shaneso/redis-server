#include <iostream>
#include <cstring>
#include <cstdint>
#include <cerrno>
#include <sys/socket.h>
#include <stdexcept>

int main() {

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  int opt_value = 1;

  int error_number = 0;

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

  return 0;

}

