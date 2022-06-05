import time
import logging
import socket

from shared_val import Led_Code

PORT = 3333

def TCP_Thread(name,shared_data,server_ip):
    
    logging.info("Thread %s: starting", name)

    while(True):

        try:
            # Create a socket (SOCK_STREAM means a TCP socket)
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                logging.info("Thread %s: Connecting to server at %s:%u", name,server_ip,PORT)
                # Connect to server and send data
                sock.connect((server_ip, PORT))

                while True:
                    rx_data = shared_data.tcp_data.barrier_read()
                    logging.info("Thread %s: Sending %d bytes", name,len(bytes(rx_data)))
                        
                    # sock.sendall(bytes(data + "\n", "utf-8"))
                    sock.sendall(bytes(rx_data))

        except Exception as e:
            logging.info("Thread %s: failed to connect, please try again! error %s",name,e)
            break
    exit(0)