"""
Tests a single connection. Copied from client.py
Author: CK
Date: Wed Apr 2
"""
import sys
import subprocess
import signal
sys.path.append('..')
from client import CandyClient, CANDY_OPT # pylint: disable=import-error,wrong-import-position

def main():
    """
    Main function which will test a single connection and then close the server.
    I like to wrap everything in a main function since you would expect inside 
    ``if __name__ == "__main__"`` to be like the "main" function of C++ but it's 
    not, it's global, namespace and everything. Awful. 
    """
    # make server
    with subprocess.Popen(['../server']) as server: # requires server to be compiled.

        # make client.
        client = CandyClient()
        assert client.fetch_candy(12, CANDY_OPT("SQUARE")) == 144
        assert client.fetch_candy(20, CANDY_OPT("BAR")) == 524287
        assert client.fetch_candy(1073741824, CANDY_OPT("DOZEN")) == 12

        # send sigint and terminate.
        # It won't terminate with 0 since we're interrupting it but that's fine.
        server.send_signal(signal.SIGINT)
        server.wait()

    print("Tests passed successfully.")

if __name__ == "__main__":
    main()
