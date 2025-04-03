#include "socket.hh"
#include "candy_factory.hh"
#include <iostream>
#include <string>
#include <thread>

namespace socket_functions {
    void handle_connection(Connection conn) {
        std::string s;
        while (true) {
            s = conn.rx(); // blocks while waiting for a message, TO-DO...
            if (s.empty()) break;
            CandyFactory candy{s};
            conn.tx(std::to_string(candy.make_candy()));
        }
    }
}

int main(int argc, char const *argv[]) {
    try {
        // Normally you'd spawn threads for multiple connections.
        PortListener pl = PortListener(8080);
        while (true) {
            Connection conn = pl.waitForConnection();
            std::thread thr{socket_functions::handle_connection, conn};
            thr.detach(); // we don't want to join as this will block main and stop from making more connections 
        }
    } 
    catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
