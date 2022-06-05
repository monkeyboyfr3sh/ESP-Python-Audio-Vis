import logging
import threading

from shared_val import SharedData

# Select threads to fork
INIT_TCP = True
INIT_UDP = True
INIT_KB = True
INIT_PA = True

from TCP_thread import TCP_Thread
from UDP_thread import UDP_Streaming_Thread
from UDP_thread import UDP_Listening_Thread
from KB_thread import KB_Thread
from PYAUDIO_thread import PYAUDIO_Thread

if __name__ == "__main__":

    myData = SharedData()

    format = "%(asctime)s: %(message)s"

    logging.basicConfig(format=format, level=logging.INFO,

                        datefmt="%H:%M:%S")

    '''

    Python audio threed captures audio for processing
    
    '''
    if(INIT_PA):
        logging.info("Main    : Creating PA thread")
        pa_t = threading.Thread(target=PYAUDIO_Thread, args=(1,myData))
        logging.info("Main    : Forking PA thread")
        pa_t.start()

    '''

    Keyboard thread reads terminal input
    
    '''
    if(INIT_KB):
        logging.info("Main    : Creating KB thread")
        kb_t = threading.Thread(target=KB_Thread, args=(2,myData))
        logging.info("Main    : Forking KB thread")
        kb_t.start()
        
    '''

    UDP thread (server) outputs audio stream
    
    '''
    if(INIT_UDP):
        logging.info("Main    : Creating UDP streaming thread")
        udp_t = threading.Thread(target=UDP_Streaming_Thread, args=(4,myData))
        logging.info("Main    : Forking UDP streaming thread")
        udp_t.start()

        logging.info("Main    : Creating UDP listening thread")
        udp_t = threading.Thread(target=UDP_Listening_Thread, args=(5,myData))
        logging.info("Main    : Forking UDP listening thread")
        udp_t.start()

    # logging.info("Main    : Waiting for TCP Thread to finish")
    # x.join()

    logging.info("Main    : all done")