import logging
import threading

from shared_val import SharedData
from TCP_thread import TCP_Thread
from UDP_thread import UDP_Thread
from KB_thread import KB_Thread
from PYAUDIO_thread import PYAUDIO_Thread

if __name__ == "__main__":

    myData = SharedData()

    format = "%(asctime)s: %(message)s"

    logging.basicConfig(format=format, level=logging.INFO,

                        datefmt="%H:%M:%S")


    logging.info("Main    : Creating TCP thread")
    tcp_t = threading.Thread(target=TCP_Thread, args=(1,myData))
    logging.info("Main    : Creating UDP thread")
    udp_t = threading.Thread(target=UDP_Thread, args=(2,myData))
    logging.info("Main    : Creating KB thread")
    kb_t = threading.Thread(target=KB_Thread, args=(3,myData))
    logging.info("Main    : Creating PA thread")
    pa_t = threading.Thread(target=PYAUDIO_Thread, args=(4,myData))

    logging.info("Main    : Forking TCP thread")
    tcp_t.start()
    logging.info("Main    : Forking UDP thread")
    udp_t.start()
    logging.info("Main    : Forking KB thread")
    kb_t.start()
    logging.info("Main    : Forking PA thread")
    pa_t.start()

    # logging.info("Main    : Waiting for TCP Thread to finish")
    # x.join()

    logging.info("Main    : all done")