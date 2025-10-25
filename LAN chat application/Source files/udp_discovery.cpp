// udp_discovery.cpp
// Simple UDP discovery: broadcaster and listener for finding the TCP server on LAN.
// Build: g++ -std=c++17 udp_discovery.cpp -o udp_discovery

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

constexpr int DISC_PORT = 9010;
constexpr int BUF_SIZE = 512;
constexpr char DISC_MSG[] = "LAN_CHAT_DISCOVERY";

void broadcaster() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    sockaddr_in bcast{};
    bcast.sin_family = AF_INET;
    bcast.sin_port = htons(DISC_PORT);
    bcast.sin_addr.s_addr = inet_addr("255.255.255.255");

    while (true) {
        sendto(sock, DISC_MSG, sizeof(DISC_MSG), 0, (sockaddr*)&bcast, sizeof(bcast));
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    close(sock);
}

void listener() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(DISC_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (sockaddr*)&addr, sizeof(addr));

    char buf[BUF_SIZE];
    sockaddr_in src{};
    socklen_t slen = sizeof(src);
    while (true) {
        ssize_t n = recvfrom(sock, buf, sizeof(buf)-1, 0, (sockaddr*)&src, &slen);
        if (n > 0) {
            buf[n] = '\\0';
            std::cout << "Discovery from " << inet_ntoa(src.sin_addr) << ": " << buf << "\\n";
        }
    }
    close(sock);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: udp_discovery [bcast|listen]\\n";
        return 0;
    }
    std::string mode = argv[1];
    if (mode == "bcast") broadcaster();
    else listener();
    return 0;
}
