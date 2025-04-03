"""
Client module for interacting with CandyFactory server.
Author: CK
Date: Wed, Apr 2 2025
"""
import socket

# Not Pythonic but I detest different casing
# in different language SDKs, so this is done
# on purpose to match the C++ enum
class CANDY_OPT: # pylint: disable=invalid-name,too-few-public-methods
    """
    Represents candy options with a specific kind.
    """
    def __init__(self, _kind: str):
        """
        Initialize a candy of kind ('SQUARE', 'BAR', 'DOZEN').
        """
        assert _kind in { 'SQUARE', 'BAR', 'DOZEN' }
        self._repr_map = {
            'SQUARE': 's',
            'BAR': 'b',
            'DOZEN': 'd'
        }
        self._kind = _kind

    def __repr__(self):
        """
        String representation of the object.
        """
        return self._repr_map[self._kind]

class CandyClient: # pylint: disable=too-few-public-methods
    """
    Client class...
    """
    def __init__(self):
        """
        Initialize object and connect to the socket.
        """
        self._client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._client_socket.connect(('127.0.0.1', 8080))

    def fetch_candy(self, _n: int, _kind: CANDY_OPT):
        """
        Requests candy of a specific kind and quantity and parses response from the server.
        """
        message = f"{_kind} {_n}"
        self._client_socket.sendall(message.encode('utf-8'))
        data = self._client_socket.recv(1024)
        return int(data.decode('utf-8'))

if __name__ == "__main__":
    client = CandyClient()
    assert client.fetch_candy(12, CANDY_OPT("SQUARE")) == 144
    assert client.fetch_candy(20, CANDY_OPT("BAR")) == 524287
    assert client.fetch_candy(1073741824, CANDY_OPT("DOZEN")) == 12
    print("Candy tests ran successfully!")
