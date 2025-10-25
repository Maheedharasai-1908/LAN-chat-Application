// tcp_client.cpp
// Simple TCP chat client.
// Build: g++ -std=c++17 tcp_client.cpp -pthread -o tcp_client

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

constexpr int SERVER_PORT = 9009;
constexpr int BUF_SIZE = 2048;

std::atomic<bool> running{true};

void recv_thread(int sockfd) {
    char buf[BUF_SIZE];
    while (running) {
        ssize_t n = recv(sockfd, buf, sizeof(buf) - 1, 0);
        if (n <= 0) break;
        buf[n] = '\0';
        std::cout << "[remote] " << buf;
        std::cout.flush();
    }
    running = false;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <server-ip>\n";
        return 1;
    }
    const char* server_ip = argv[1];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); return 1; }

    sockaddr_in srv{};
    srv.sin_family = AF_INET;
    srv.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, server_ip, &srv.sin_addr);

    if (connect(sockfd, (sockaddr*)&srv, sizeof(srv)) < 0) { perror("connect"); return 1; }

    std::thread t(recv_thread, sockfd);

    std::string line;
    while (running && std::getline(std::cin, line)) {
        line += "\\n";
        send(sockfd, line.c_str(), line.size(), 0);
    }

    running = false;
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
    if (t.joinable()) t.join();
    return 0;
}
