#include "socket.hh"
#include <iostream>

#include "client.hh"
#include "candy.hh"
#include <cassert>

// Example, fetches candy...
int main(int argc, char const *argv[]) {
    try {
        CandyClient client{};
        assert(client.fetch_candy(12, CANDY_OPT::SQUARE) == 144);
        assert(client.fetch_candy(20, CANDY_OPT::BAR) == 524287);
        assert(client.fetch_candy(1073741824, CANDY_OPT::DOZEN) == 12);
        std::cout << "Fetching candy successful!" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
