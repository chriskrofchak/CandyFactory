#ifndef CANDY_HH 
#define CANDY_HH 

#include <string>
#include <vector>

enum CANDY_OPT {
    SQUARE = 0,
    BAR,
    DOZEN
};

CANDY_OPT stocandy_opt(const std::string &s) {
    std::vector<std::string> options = { "s", "b", "d" };
    std::vector<std::string>::iterator it = std::find(options.begin(), options.end(), s);
    if (it == options.end()) throw std::runtime_error("Invalid Option Passed");
    // it != options.end(), so subtract it to get distance 
    // and initialize CANDY_OPT which under the hood is an integer
    return static_cast<CANDY_OPT>(it - options.begin());
}

// In a functional language something being exhaustive is 
// checked by the compiler - but this is an enum, and a small one, 
// so we can see that our match arms are in fact exhaustive.
std::string candy_opttos(const CANDY_OPT &kind) {
    switch (kind) {
        case CANDY_OPT::SQUARE: return std::string{"s"};
        case CANDY_OPT::BAR:    return std::string{"b"};
        case CANDY_OPT::DOZEN:  return std::string{"d"};
        default:                return std::string{"SHOULD. NOT. HAPPEN."};
    }
}

#endif 