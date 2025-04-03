"""
Tests many connections. Copied from client.py
Author: CK
Date: Wed Apr 2
"""
import sys
import subprocess
import threading
import signal
# this is very bad practice
# as this requires the python script to be run in the tests
# but I don't really care these are proofs of concept if anything.
sys.path.append('..')
from client import CandyClient, CANDY_OPT # pylint: disable=import-error,wrong-import-position

def thread1(i: int):
    """
    A thread function which will make a single client and test the results.
    """
    client = CandyClient()
    try:
        assert client.fetch_candy(12, CANDY_OPT("SQUARE")) == 144
        assert client.fetch_candy(20, CANDY_OPT("BAR")) == 524287
        assert client.fetch_candy(1073741824, CANDY_OPT("DOZEN")) == 12
    except AssertionError as _:
        thread_results[i] = False # pylint: disable=possibly-used-before-assignment
    else:
        thread_results[i] = True


def main():
    """
    Refer to test_single_connection.py for my diatribe on main functions. 
    """
    with subprocess.Popen(['../server']) as server: # requires server to be compiled.

        threads = []

        for i in range(N): # pylint: disable=possibly-used-before-assignment
            thread = threading.Thread(target=thread1, args=(i,))
            threads.append(thread)

        # start threads
        for thread in threads:
            thread.start()

        for thread in threads:
            thread.join()

        assert all(thread_results), "One or more threads failed."

        # send sigint and terminate.
        server.send_signal(signal.SIGINT)
        server.wait()

    print("Tests passed successfully.")

if __name__ == "__main__":
    # global variables to share between threads...
    # python lists are thread-safe!
    # we can see the two variables are initialized before calling
    # main so we can disable pylint's warnings.
    N = 10
    thread_results = [ False ] * N
    main()
