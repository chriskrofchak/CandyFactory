#include "socket.hh"
#include "candy_factory.hh"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
    try {
        // Normally you'd spawn threads for multiple connections.
        Connection conn = PortListener(8080).waitForConnection();
        std::string s;
        while (true) {
            s = conn.rx(); // blocks while waiting for a message, TO-DO...
            if (s.empty()) break;
            CandyFactory candy{s};
            conn.tx(std::to_string(candy.make_candy()));
        }
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
