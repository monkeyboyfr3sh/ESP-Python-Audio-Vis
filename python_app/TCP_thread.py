import time
import logging
import socket

from shared_val import Led_Code

def TCP_Thread(name,shared_data):

    # Config thread
    HOST, PORT = "192.168.0.126", 3333
    
    logging.info("Thread %s: starting", name)

    while(True):

        try:
            # Create a socket (SOCK_STREAM means a TCP socket)
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                # Connect to server and send data
                sock.connect((HOST, PORT))

                while True:
                    rx_data = shared_data.tcp_data.barrier_read()
                    logging.info("Thread %s: Sending %d bytes", name,len(bytes(rx_data)))
                        
                    # sock.sendall(bytes(data + "\n", "utf-8"))
                    sock.sendall(bytes(rx_data))

        except:
            logging.info("Thread %s: failed to connect, please try again!", name)
    exit(0)