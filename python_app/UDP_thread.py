import time
import logging
import socket

def UDP_Thread(name,shared_data):
    
    # Config thread 
    LOCALIP, PORT = "192.168.0.166", 20001
    BUFFERSIZE  = 1024

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Bind to address and ip
    UDPServerSocket.bind((LOCALIP, PORT))

    logging.info("Thread %s: UDP server up and listening", name)

    got_address = False

    udp_timestamp_ms = shared_data.millis()

    # Listen for incoming datagrams
    while(True):

        if not (got_address):
            bytesAddressPair = UDPServerSocket.recvfrom(BUFFERSIZE)
            # message = bytesAddressPair[0]
            address = bytesAddressPair[1]
            print(address)
            got_address = True
            logging.info("Thread %s: Sending UDP data to client", name)

        if(shared_data.millis()-udp_timestamp_ms > 5):
            udp_timestamp_ms = shared_data.millis()

            # Sending a reply to client
            UDPServerSocket.sendto(shared_data.udp_data, address)