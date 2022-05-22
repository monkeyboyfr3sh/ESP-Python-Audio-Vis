import time
import logging
import socket

def TCP_Thread(name,shared_data):
    HOST, PORT = "192.168.0.127", 3333

    logging.info("Thread %s: starting", name)

    while(True):
        # Create a socket (SOCK_STREAM means a TCP socket)
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            # Connect to server and send data
            sock.connect((HOST, PORT))
            
            while True:
                rx_data = shared_data.read_tcp_data_barrier()

                logging.info("Thread %s: Sending %d bytes", name,len(bytes(rx_data)))
                    
                # sock.sendall(bytes(data + "\n", "utf-8"))
                sock.sendall(bytes(rx_data))
                
                # # Receive data from the server and shut down
                # received = str(sock.recv(1024), "utf-8")
                # time.sleep(0.1)

    exit(0)