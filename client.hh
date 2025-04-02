#ifndef CLIENT_HH
#define CLIENT_HH 

#include "socket.hh"
#include "candy.hh"
#include <sstream>

class CandyClient {
    Connection _conn;
public:
    CandyClient() : _conn{Connection{"127.0.0.1", 8080}} {}

    int fetch_candy(int _n, CANDY_OPT _kind) {
        std::stringstream s;
        s << candy_opttos(_kind) << " " << std::to_string(_n);
        _conn.tx(s.str());
        return std::stoi(_conn.rx());
    }
};

#endif 