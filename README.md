# Candy Factory 

### Summary

This is a small code example which uses sockets on `127.0.0.1:8080` to send messages from a "client" to a "server."

There are options for a "square" candy, a candy "bar," or a "dozen" pieces of candy. Feel free to walk through the code or run and connect to the server to see what these options do!

### Server

The server is written in C++. I have updated it to be multi-threaded but this is still not going to be anywhere near as performant as it could be. However, solving the [C10K](http://www.kegel.com/c10k.html) problem is not what I sought out to do, so I have left it as is - dispatching a single thread per connection. I have never programmed sockets before, having used Apache Pulsar on a previous internship for message passing, so I've used a sample code, cited, from a Stack Exchange answer. The code wasn't correct so I fixed it, but kept the object-oriented style as it fits well in C++.

### Clients 

Both clients are called `CandyClient` and have no parameters for initialization.

#### C++

The C++ client is located in `client.cc`, and has `fetch_candy` which takes an integer and a member of the `CANDY_OPT` enum defined in "candy.hh". 

#### Python

There is a simple Python client named `CandyClient` which offers the function `fetch_candy` which takes in an integer and an instantiated Python class `CANDY_OPT` which expects one of `{ "SQUARE", "BAR", "DOZEN" }`. The capitalization, going against typical Python class naming is to mimic the C++ enum of the same name which describes which candy you should order. 

### Pitfalls

#### Error Handling 

This is a toy example and so the error handling is not complete, or elegant. I've kept most of the `std::runtime_error` from the sample socket code in, and I've thrown my own runtime errors as well. Typically, as far as handling the production of candy goes, these should be caught on one the server side, handled elegantly and send back an appropriate message to the client, to be handled as well on that side. 

I'm using this as an example of a way of passing information between programs because, as we can see, it requires only a few files to set up server/client classes. Nicely, in Python only a single file for a client which can now communicate with a C++ suite, without the need for any special bindings through C. 

#### Portability 

This solution, unfortunately, given I made this example to demonstrate interoperability, is not going to be very portable to Windows. I will have to boot up an old Windows computer at home and try to see if it works but likely it won't for two reasons: the way socket connections are made in Windows differs from Unix-like systems (I think even an extra import in C++ Winsock, is needed), and the way threads are handled are different on Windows than on Unix. Technically, Mac is the only true POSIX compliant OS currently, but Linux virtually is and can easily be made POSIX compliant, and for this example, is. 

An alternative would be the library BOOST for C++ which is very popular, and also portable. The drawback with Boost is that it is very large and so for this example was omitted.


