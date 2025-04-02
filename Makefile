CXX=g++
CXXFLAGS=-std=c++14

all: client server

client:
	$(CXX) client.cc -o $@ $(CXXFLAGS)

server:
	$(CXX) server.cc -o $@ $(CXXFLAGS)

.PHONY: clean all

clean:
	rm server client