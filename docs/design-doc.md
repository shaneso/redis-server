## Redis Server Design Doc

### Properties

**Protocol**: TCP/IP

**Data Store**: Persistence via RDB (snapshots) + AOF (Append-Only File)

### Architecture

**Socket Programming**

| Method      | Purpose                                                 |
| ------      | -------                                                 |
| `socket()`  | Allocates and returns a socket handle (`fd`)            |
| `bind()`    | Sets the listening socket's IP port                     |
| `listen()`  | Create a listening socket                               |
| `connect()` | Create a TCP connection                                 |
| `accept()`  | Wait for incoming TCP connections                       |
| `read()`    | Reads data from byte stream                             |
| `write()`   | Write data to byte stream                               |
| `close()`   | Close the socket connection and free up space for OS    |

**UNIX Syscall and Kernel Space API Documentation**

Documentation for Linux and POSIX syscalls and API methods can be accessed
by running the `man` page commands provided in the terminal. You will find
the name, synopsis, and descriptions for commands (`1`), syscalls (`2`),
lib functions (`3`), and misc (`7`).

| Name | Synopsis | Documentation |
| ---- | -------- | ------------- |
| `socket` | `#include <sys/socket.h>` | `man 7 socket` |
| `setsockopt` | `#include <sys/socket.h>` | `man 3p setsockopt` |
| `bind` | `#include <sys/socket.h>` | `man 2 bind` |
| `getprotoent` | `#include <netdb.h>` | `man 3 getprotoent` |
| `ip` | `#include <netinet/ip.h>` | `man 7 ip` |
| `tcp` | `#include <netinet/tcp.h>` | `man 7 tcp` |

**Socket Connection Reusability and MSL Override**

The `SO_REUSEADDR` option is used to modify socket connection behaviour.
A common edge case in network programs is an event where a new program
instance fails to connect to a previously used TCP port with stale
packets. The `TIME_WAIT` state is established when a TCP connection is
terminated via the four-way handshake to prevent loose packets from
carrying over to a new program instance using the same port. In the
syscall `setsockopt()` the `TIME_WAIT` period can be bypassed with the
`SO_REUSEADDR` parameter.

**TCP Server**

Pseudocode

```
fd = socket() // man 7 socket
bind(fd, address)
listen(fd)
while true:
  conn_fd = accept(fd)
  process(fd)
  close(fd)
```
