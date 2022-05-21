import socket
import time
import logging
import threading
import sys

HOST, PORT = "192.168.0.74", 3333
# data = "My data!".join(sys.argv[1:])
# data = "My data!"
data1 = (1,2,3,4)
data2 = (1,2,3)

def TCP_Thread(name):
    
    logging.info("Thread %s: starting", name)

    # Create a socket (SOCK_STREAM means a TCP socket)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        # Connect to server and send data
        sock.connect((HOST, PORT))
        
        prev = False
        while True:
            if(prev):
                logging.info("Thread %s: Sending %d bytes", name,len(bytes(data1)))
                
                # sock.sendall(bytes(data + "\n", "utf-8"))
                sock.sendall(bytes(data1))
            else :
                logging.info("Thread %s: Sending %d bytes", name,len(bytes(data2)))
                
                # sock.sendall(bytes(data + "\n", "utf-8"))
                sock.sendall(bytes(data2))
            # Receive data from the server and shut down
            received = str(sock.recv(1024), "utf-8")

            time.sleep(1)    

if __name__ == "__main__":

    format = "%(asctime)s: %(message)s"

    logging.basicConfig(format=format, level=logging.INFO,

                        datefmt="%H:%M:%S")


    logging.info("Main    : Creating TCP thread")
    x = threading.Thread(target=TCP_Thread, args=(1,))

    logging.info("Main    : Forking TCP thread")
    x.start()

    logging.info("Main    : Waiting for TCP Thread to finish")
    x.join()

    logging.info("Main    : all done")