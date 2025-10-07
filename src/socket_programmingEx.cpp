#include <iostream>
#include <string>
#include <vector>
#include <cstring> // For memset
#include <fstream> // For file I/O
#include <ctime>   // For time
#include <sstream> // For std::ostringstream
#include <iomanip> // For std::put_time
#include "helloEx.h" // for printLine
#include "socket_programmingEx.h"

// Platform-specific includes and setup
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
    #define SOCKET_TYPE SOCKET
    #define INVALID_SOCKET_VAL INVALID_SOCKET
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define CLOSE_SOCKET close
    #define SOCKET_TYPE int
    #define INVALID_SOCKET_VAL -1
#endif

const int PORT = 8080;

// --- Logging Functionality ---

/**
 * @brief Gets the current system time as a formatted string.
 * @return A string representing the current timestamp (e.g., "YYYY-MM-DD HH:MM:SS").
 */
static std::string getCurrentTimestamp() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

/**
 * @brief Writes a log entry to the "log.txt" file.
 * @param level The log level (e.g., "INFO", "ERROR").
 * @param message The log message.
 */
static void write_log(const std::string& level, const std::string& message) {
    std::ofstream log_file("log.txt", std::ios_base::app); // Open in append mode
    if (log_file.is_open()) {
        log_file << "[" << getCurrentTimestamp() << "] [" << level << "] " << message << std::endl;
    }
}

/**
 * @brief Runs a simple TCP echo server.
 */
static void run_tcp_server() {
    printLine("Starting TCP Echo Server");
    write_log("INFO", "Server starting up.");

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }
#endif

    SOCKET_TYPE server_fd, new_socket;
    sockaddr_in address;
    int addrlen = sizeof(address);

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET_VAL) {
        std::cerr << "Socket creation failed" << std::endl;
        write_log("ERROR", "Server socket creation failed.");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces
    address.sin_port = htons(PORT);       // Host to network short byte order

    // 2. Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        write_log("ERROR", "Server socket bind failed.");
        CLOSE_SOCKET(server_fd);
        return;
    }

    // 3. Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        write_log("ERROR", "Server socket listen failed.");
        CLOSE_SOCKET(server_fd);
        return;
    }

    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // 4. Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) == INVALID_SOCKET_VAL) {
        std::cerr << "Accept failed" << std::endl;
        write_log("ERROR", "Server socket accept failed.");
        CLOSE_SOCKET(server_fd);
        return;
    }

    std::cout << "Client connected." << std::endl;
    write_log("INFO", "Client connected.");

    // 5. Read data from the client and echo it back
    char buffer[1024] = {0};
    long valread = recv(new_socket, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Received from client: " << buffer << std::endl;
        write_log("INFO", "Received message: " + std::string(buffer));
        send(new_socket, buffer, strlen(buffer), 0);
        std::cout << "Echoed message back to client." << std::endl;
    }

    // 6. Close sockets
    CLOSE_SOCKET(new_socket);
    CLOSE_SOCKET(server_fd);
    write_log("INFO", "Server shutting down.");

#ifdef _WIN32
    WSACleanup();
#endif
}

/**
 * @brief Runs a simple TCP client to connect to the echo server.
 */
static void run_tcp_client() {
    printLine("Starting TCP Client");
    write_log("INFO", "Client starting up.");

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }
#endif

    SOCKET_TYPE sock = 0;
    sockaddr_in serv_addr;
    const char* hello = "Hello from client!";
    char buffer[1024] = {0};

    // 1. Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET_VAL) {
        std::cerr << "Socket creation error" << std::endl;
        write_log("ERROR", "Client socket creation failed.");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        write_log("ERROR", "Invalid server address.");
        return;
    }

    // 2. Connect to the server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        write_log("ERROR", "Connection to server failed.");
        std::cerr << "Connection Failed" << std::endl;
        return;
    }

    // 3. Send data to the server
    send(sock, hello, strlen(hello), 0);
    std::cout << "Message sent to server: " << hello << std::endl;
    write_log("INFO", "Sent message: " + std::string(hello));

    // 4. Read the echoed data from the server
    long valread = recv(sock, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Received from server: " << buffer << std::endl;
        write_log("INFO", "Received echo: " + std::string(buffer));
    }

    // 5. Close the socket
    CLOSE_SOCKET(sock);
    write_log("INFO", "Client shutting down.");

#ifdef _WIN32
    WSACleanup();
#endif
}

void socket_programmingEx(void) {
    int choice = 0;
    std::cout << "--- Socket Programming Menu ---\n";
    std::cout << "1. Run as TCP Server\n";
    std::cout << "2. Run as TCP Client\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        run_tcp_server();
    } else if (choice == 2) {
        run_tcp_client();
    } else {
        std::cout << "Invalid choice." << std::endl;
    }
}