# LAN-chat-Application
LAN Chat Application — A lightweight local network chat tool that enables real-time messaging between users on the same LAN using socket communication. No internet or external server required.
# LAN Chat Application (C++ - TCP & UDP)

## Overview
This is a small LAN chat project written in C++:
- `tcp_server` — multithreaded TCP server that relays messages between connected clients.
- `tcp_client` — TCP client for connecting to the server and exchanging chat messages.
- `udp_discovery` — simple UDP-based LAN discovery (broadcast) to locate peers/servers.

## Build
Requires a Linux environment with g++.
```
make
```

## Run
1. Start server on a machine in LAN:
```
./tcp_server
```
2. Optionally use discovery in listener mode on server machine:
```
./udp_discovery listen
```
3. On a client machine, either run discovery to find server IP or start client with server IP:
```
./udp_discovery listen     # to see discovery packets
./tcp_client <server-ip>
```

## Notes & Extensions
- Add authentication, message framing, GUI client, TLS (openssl), or switch to epoll for scalability.
- The current code is kept simple for clarity; production-quality code requires robust error handling and resource management.
