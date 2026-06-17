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

### Valgrind Memory and Cache Profiling

**Cache Profiling Commands**

| Command                                       | Description                                                              |
| -------                                       | -----------                                                              |
| `valgrind --tool=cachegrind ./<program>`      | Runs Cachegrind on `<program>` and outputs a `cachegrind.out.<pid>` file |
| `cg_annotate cachegrind.out.<pid>`            | Processes the simulation output file into readable text                  |

**Note**: More information on Valgrind commands can be retrieved by running `man 1 valgrind`. The `--cache-sim=yes` tag
is used to enable collection of cache access and miss counts. This is important for tracking cache in multiple tiers,
which is important when computing instruction performance ratios and benchmarking CPU efficiency.

**Metrics**

| Metric | Measurement                      | Description                    |
| ------ | -----------                      | -----------                    |
| `Dlmr` | `L1` data cache misses (reads)   | Frequency of missing hot data  |
| `Dlmw` | `L1` data cache misses (writes)  | Write performance              |
| `LLdr` | Last-level cache misses          | Frequency of fetching from RAM |
| `LLdw` | Last-level cache misses (writes) | Memory bandwith bottleneck     |
| `Dr`   | Data cache reads                 | Program data read count        |
| `Dw`   | Data cache writes                | Program data write count       |

**Note**: The objective of cache performance optimization is to minimize
`LLdr` and `LLdw` aggressively, while still maintaining low cache misses on
`L2` and `L3`. This is because cache offsetting at the last-level cache (RAM)
is much more costly compared to hitting on-chip cache tiers.

