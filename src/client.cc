// system
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
// stdlib
#include <cerrno>
#include <cstring>
#include <iostream>

int main() {

  int sockfd; // fd

  ssize_t retval; // return value

  // socket

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1)
    std::cerr << "socket error" << std::endl;

  // sockaddr

  struct sockaddr_in cli_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(6379),
    .sin_addr = {
      .s_addr = htonl(INADDR_LOOPBACK)
    },
    .sin_zero = {}
  };

  // connect

  if (connect(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)))
    std::cerr << "connect error" << std::endl;
  
  // send

  char wbuf[] = "hello";

  retval = send(sockfd, wbuf, std::strlen(wbuf), 0);

  if (retval == -1)
    std::cerr << "send error" << std::endl;

  // read

  char rbuf[64] = {};

  retval = recv(sockfd, rbuf, sizeof(rbuf) - 1, 0);

  if (retval == -1)
    std::cerr << "receive error" << std::endl;
  
  // print

  std::cout << "server: " << rbuf << std::endl;

  // close

  close(sockfd);

}

