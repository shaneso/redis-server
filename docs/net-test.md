## Network Testing

### LAN Client-Server Connection

**Note**: The host machine running the server may be blocked for
incoming connections by the firewall. Users may bypass the firewall
by allowing inbound TCP connection requests at the specified IP port.

After running `ip a` in the terminal, find the IPv4 address beside
`inet`. This address is the socket internet address value which the
`sockaddr_in` client fd is initialized to.

The server will use the `INADDR_ANY` macro for its `sockaddr_in` address
scheme, which is equivalent to `0.0.0.0` in IPv4.

Once these values have been set, the user may run the server and the client
on separate machines within the LAN.

**Note**: If the user is running the server in WSL, the IP address may not
match with the host machine scheme on Windows. To solve this, a `.wslconfig`
file may be created in the `%USERNAME$` directory with the contents

```
[wsl2]
networkingMode=mirrored
dnsTunnel=true
```

Save the file and run `wsl --shutdown` in the terminal, then start WSL. When the user runs `ip a` the native IP address should show now.

