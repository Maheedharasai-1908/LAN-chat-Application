# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -O2 -pthread

all: tcp_server tcp_client udp_discovery

tcp_server: tcp_server.cpp
	$(CXX) $(CXXFLAGS) tcp_server.cpp -o tcp_server

tcp_client: tcp_client.cpp
	$(CXX) $(CXXFLAGS) tcp_client.cpp -o tcp_client

udp_discovery: udp_discovery.cpp
	$(CXX) -std=c++17 udp_discovery.cpp -o udp_discovery

clean:
	rm -f tcp_server tcp_client udp_discovery
