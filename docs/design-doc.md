## Redis Server Design Doc

### Properties

**Protocol**: TCP/IP

**Data Store**: Persistence via RDB (snapshots) + AOF (Append-Only File)

### Proposed Features

- RDB persistence for permanent data and kv storage
- `epoll` API and event-based concurrency

### Architecture

**Socket Programming**

| Method      | Purpose                                                |
| ------      | -------                                                |
| `socket()`  | Allocates and returns a socket handle (`fd`)           |
| `bind()`    | Sets the listening socket's IP port                    |
| `listen()`  | Creates a listening socket                             |
| `connect()` | Creates a TCP connection                               |
| `accept()`  | Waits for incoming TCP connections                     |
| `read()`    | Reads data from byte stream                            |
| `write()`   | Writes data to byte stream                             |
| `close()`   | Closes the socket connection and frees up space for OS |

**UNIX C Library, Syscall, and Kernel Space API Documentation**

Documentation for Linux and POSIX syscalls and API methods can be accessed
by running the `man` page commands provided in the terminal. You will find
the name, synopsis, and descriptions for commands (`1`), syscalls (`2`),
lib functions (`3`), and misc (`7`).

| Name          | Synopsis                   | Documentation           |
| ----          | --------                   | -------------           |
| `accept`      | `#include <sys/socket.h>`  | `man 2 accept`          |
| `bind`        | `#include <sys/socket.h>`  | `man 2 bind`            |
| `epoll`       | `#include <sys/epoll.h>`   | `man 7 epoll`           |
| `getprotoent` | `#include <netdb.h>`       | `man 3 getprotoent`     |
| `ip`          | `#include <netinet/ip.h>`  | `man 7 ip`              |
| `listen`      | `#include <sys/socket.h>`  | `man 2 listen`          |
| `recv`        | `#include <sys/socket.h>`  | `man 2 recv`            |
| `send`        | `#include <sys/socket.h>`  | `man 2 send`            |
| `setsockopt`  | `#include <sys/socket.h>`  | `man 3p setsockopt`     |
| `size_t`      | `#include <stddef.h>`      | `man 3type size_t`      |
| `ssize_t`     | `#include <sys/types.h>`   | `man 3type ssize_t`     |
| `socket`      | `#include <sys/socket.h>`  | `man 2 socket`          |
| `socket`      | `#include <sys/socket.h>`  | `man 7 socket`          |
| `sockaddr`    | `#include <sys/socket.h>`  | `man 3type sockaddr`    |
| `sockaddr_in` | `#include <netinet/in.h>`  | `man 3type sockaddr_in` |
| `tcp`         | `#include <netinet/tcp.h>` | `man 7 tcp`             |

**Socket Connection Reusability and MSL Override**

The `SO_REUSEADDR` option is used to modify socket connection behaviour.
A common edge case in network programs is an event where a new program
instance fails to connect to a previously used TCP port with stale
packets. The `TIME_WAIT` state is established when a TCP connection is
terminated via the four-way handshake to prevent loose packets from
carrying over to a new program instance using the same port. In the
syscall `setsockopt()` the `TIME_WAIT` period can be bypassed with the
`SO_REUSEADDR` parameter.

**IPv4 Internet Socket Address Description**

To specify the IP address and port for the TCP server, the `sockaddr_in`
struct from the `netinet/in.h` package is used. In this struct, the
socket internet family, port, and address can be initialized.

**Endianness and Byte Order**

Most modern architectures, including x86 and ARM, run in little-endian.
Network byte orders in protocols like TCP/IP, however, are big-endian.
To bridge the host layer with the network layer, the `hton`
(host-to-network) and `ntoh` (network-to-host) functions from the
`arpa/inet.h` library are used. Officially, the function names have
suffixes, such as `s` for short and `l` for long, depending on the use
case and byte size required. A table containing the endian reversal
functions is provided for reference. Additional information is provided
in the library functions manual on `man 3 byteorder`.

| Function | Description                                                        |
| -------- | -----------                                                        |
| `htons`  | Converts an unsigned short integer from host to network byte order |
| `htonl`  | Converts an unsigned integer from host to network byte order       |
| `ntohs`  | Converts an unsigned short integer from network to host byte order |
| `ntohl`  | Converts an unsigned integer from network to host byte order       |

**Socket I/O**

For data transmission on a socket, the `recv` and `send` syscalls will be used.
Since both operations may return `-1` when an error has occured, the `ssize_t`
data type will be used to retrieve the return value. The `recv` call is for
reading buffer data and `send` is for writing data to the buffer.

**TCP Server**

Pseudocode

```
fd = socket()
bind(fd, address)
listen(fd)
while true:
  conn_fd = accept(fd)
  process(fd)
  close(fd)
```

**TCP Client**

Pseudocode

```
fd = socket()
connect(fd)
while true:
  send(fd)
  recv(fd)
close(fd)
```
