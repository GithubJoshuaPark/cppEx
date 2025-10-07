#include <iostream>
#include <string>
#include <vector>
#include "helloEx.h" // Note: This file uses C-style printf
#include "networking_basicsEx.h"

// Platform-specific includes for networking
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib") // Link with the Winsock library
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

void networking_basicsEx(void) {
    printLine("Networking Basics: DNS Lookup");

#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }
#endif

    const char* hostname = "www.google.com";
    std::cout << "Performing DNS lookup for: " << hostname << std::endl;

    addrinfo hints = {};
    hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* result = nullptr;
    int status = getaddrinfo(hostname, nullptr, &hints, &result);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
    } else {
        std::cout << "IP addresses found:" << std::endl;
        for (addrinfo* p = result; p != nullptr; p = p->ai_next) {
            void* addr;
            char ipstr[INET6_ADDRSTRLEN];

            if (p->ai_family == AF_INET) { // IPv4
                sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(p->ai_addr);
                addr = &(ipv4->sin_addr);
                std::cout << "  IPv4: ";
            } else { // IPv6
                sockaddr_in6* ipv6 = reinterpret_cast<sockaddr_in6*>(p->ai_addr);
                addr = &(ipv6->sin6_addr);
                std::cout << "  IPv6: ";
            }

            // Convert the IP to a string and print it
            inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
            std::cout << ipstr << std::endl;
        }
        freeaddrinfo(result); // Free the linked list
    }

#ifdef _WIN32
    WSACleanup();
#endif
}