from typing import Literal
import socket

# Not Pythonic but I detest different casing 
# in different language SDKs. 
class CANDY_OPT:
    def __init__(self, _kind: str):
        assert _kind in { 'SQUARE', 'BAR', 'DOZEN' }
        self._kind = _kind
    
    def __repr__(self):
        return { 'SQUARE': 's', 'BAR': 'b', 'DOZEN': 'd' }[self._kind]

class CandyClient:
    def __init__(self):
        self._client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._client_socket.connect(('127.0.0.1', 8080))

    def fetch_candy(self, _n: int, _kind: CANDY_OPT):
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