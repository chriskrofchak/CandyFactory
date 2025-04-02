#ifndef CANDY_FACTORY_HH
#define CANDY_FACTORY_HH

#include <sstream>
#include <vector>
#include <string>
#include "candy.hh"

class CandyFactory {
    int       _n;
    CANDY_OPT _kind;
    std::istringstream _buffer;
    std::vector<std::string> _tokens;
public:
    CandyFactory(int _n) : _n{_n}, _kind{CANDY_OPT::SQUARE} {}
    CandyFactory(int _n, CANDY_OPT _kind) : _n{_n}, _kind{_kind} {}
    CandyFactory(const std::string &m) : 
        _buffer{m}
    {
        _tokens = std::vector<std::string>{std::istream_iterator<std::string>{_buffer}, std::istream_iterator<std::string>{}};
        _kind   = stocandy_opt(_tokens.at(0));
        _n      = std::stoi(_tokens.at(1)); 
    }

    // { N 2 }
    int _bar(int _n) {
        int x = 1;
        for (int i = 1; i < _n; i++) x *= 2;
        return x - 1;
    }

    int make_candy() {
        switch (_kind) {
            case CANDY_OPT::SQUARE: return _n*_n;
            case CANDY_OPT::BAR:    return _bar(_n);
            case CANDY_OPT::DOZEN:  return 12;
            default:                return -1; // Shouldn't happen 
        }
    }
};

#endif 