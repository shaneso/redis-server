// system
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
// stdlib
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
// project
#include "err.h"

#define BACKLOG SOMAXCONN // Socket max connections (/proc/sys/net)

/**
 * @brief Processes buffer data I/O
 * 
 * @param connfd is the connection-mode socket handle
 */
void proc(int connfd) {
  int retval;
  char rbuf[64] = {};

  retval = recv(connfd, rbuf, sizeof(rbuf) - 1, 0);
  if (retval == -1)
    err(EXIT_FAILURE, "Receive");

  std::cout << "Client: " << rbuf << std::endl;

  char wbuf[] = "world";
  retval = send(connfd, wbuf, std::strlen(wbuf), 0);
  if (retval == -1)
    err(EXIT_FAILURE, "Send");
}

int main() {

  int sockfd, connfd; // Socket handles for server and client
  int retval; // Return value
  socklen_t addrlen_s, addrlen_c; // Server and client socket address lengths

  // Create socket handle (fd)
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // Check socket handle has been returned successfully
  if (sockfd == -1)
    err(EXIT_FAILURE, "Socket");

  int opt_value = 1; // Set socket option value param

  // Set socket options
  retval = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_value, sizeof(opt_value));
  // Check if socket options have been set
  if (retval == -1)
    err(EXIT_FAILURE, "Socket option");

  // Initialize server socket endpoint scheme
  struct sockaddr_in serv_addr = {
    .sin_family = AF_INET, // IPv4 address scheme
    .sin_port = htons(6379), // Default Redis data store port 6379
    .sin_addr = {
      .s_addr = htonl((127 << 24) | (0 << 16) | (0 << 8) | 1) // Localhost 127.0.0.1
    },
    .sin_zero = {} // Byte padding for struct memory alignment
  };

  addrlen_s = sizeof(serv_addr); // Set server address byte length

  // Bind selected IP address and port to socket
  // addrlen_s passed to bind syscall as socklen_t
  retval = bind(sockfd, (struct sockaddr*) &serv_addr, addrlen_s);

  // Check bind status
  if (retval == -1)
    err(EXIT_FAILURE, "Bind");
  
  // Listen for connections on a socket
  retval = listen(sockfd, BACKLOG);

  // Check if socket is established as passive
  if (retval == -1)
    err(EXIT_FAILURE, "Listen");
  
  // Initialize client socket endpoint scheme
  struct sockaddr_in client_addr = {};

  // Accept and handle client connections
  while (1) {
    // Initialize client endpoint address length (IP protocol-agnostic)
    addrlen_c = sizeof(client_addr);
    // Accept client connection request and return socket handle
    // addrlen_c passed to accept syscall as pointer
    connfd = accept(sockfd, (struct sockaddr*) &client_addr, &addrlen_c);
    // Check if client connection request has been accepted
    if (connfd == -1)
      err(EXIT_FAILURE, "Accept");
    proc(connfd);
    close(connfd);
  }

  close(sockfd);

  return EXIT_SUCCESS;
}

