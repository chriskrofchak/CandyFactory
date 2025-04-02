#ifndef SOCKET_HH 
#define SOCKET_HH 

// Taken from:
// https://stackoverflow.com/questions/3509011/socket-programming-in-c 
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>


class Socket {
    int _sock;
public:
    Socket(int socket) : _sock{socket} {
        if (_sock < 0) throw std::runtime_error("Socket creation error");
    }
    Socket() : Socket(socket(AF_INET, SOCK_STREAM, 0)) {}
    std::string rx() {
        char buffer[1024] = {0};
        int n = read(_sock, buffer, sizeof(buffer));
        return std::string(buffer, n);
    }
    void tx(std::string s) {
        send(_sock, s.c_str(), s.length(), 0);
    }
    int get_socket() {
        return _sock;
    }
};

class Connection: public Socket {
public:
    Connection(int socket) : Socket{socket} {}
    Connection(std::string address,unsigned short port): Socket()
    {
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(
            AF_INET,
            address.c_str(),
            &serv_addr.sin_addr
        ) <= 0) throw std::runtime_error("Invalid address: Address not supported");

        if (connect(
            get_socket(),
            (struct sockaddr *)&serv_addr,
            sizeof(serv_addr)
        ) < 0) throw std::runtime_error("\nConnection Failed \n");
    }
};

class PortListener {
    Socket server; // fd is created in default Socket constructor
    struct sockaddr_in address;
    int opt = 1;
public:
    PortListener(unsigned short port) : server{}, address{} {

        // Setting Socket options - not or'ing SO_REUSEADDR and SO_REUSEPORT 
        // is not supported, even though checking the definitions they're powers of 2
        // I don't think setsockopt parses it like that?
        if (setsockopt(
            server.get_socket(),
            SOL_SOCKET,
            SO_REUSEADDR,
            &opt,
            sizeof(opt)
        ) || setsockopt(
            server.get_socket(),
            SOL_SOCKET,
            SO_REUSEPORT,
            &opt,
            sizeof(opt)
        )) throw std::runtime_error("setsockopt: " + std::to_string(errno));

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( port );

        // Bind to 8080
        if (bind(
            server.get_socket(),
            (struct sockaddr *)&address,
            sizeof(address)
        ) < 0) throw std::runtime_error("Bind failed.");

        // Start listening
        if (listen(server.get_socket(), 3) < 0) {
            throw std::runtime_error("Listen failed.");
        }
    }
    Connection waitForConnection() {
        int new_socket;
        int addrlen = sizeof(struct sockaddr_in);
        new_socket = accept(
            server.get_socket(),
            (struct sockaddr *)&address,
            (socklen_t*)&addrlen
        );
        if (new_socket < 0) throw std::runtime_error("Accept failed.");
        return Connection(new_socket);
    }
};

#endif