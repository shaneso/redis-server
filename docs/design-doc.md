## Redis Server Design Doc

### Properties

**Protocol**: TCP/IP

**Data Store**: Persistence via RDB (snapshots) + AOF (Append-Only File)

### Architecture

**Socket Programming**

| Method | Purpose |
| ------ | ------- |
| `socket()` | Allocates and returns a socket handle (`fd`) |
| `bind()` | Sets the listening socket's IP port |
| `listen()` | Create a listening socket |
| `connect()` | Create a TCP connection |
| `accept()` | Wait for incoming TCP connections |
| `read()` | Reads data from byte stream |
| `write()` | Write data to byte stream |
| `close()` | Close the socket connection and free up space for OS |
