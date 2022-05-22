import time
import logging
import socket

def UDP_Thread(name,shared_data):
    localIP     = "192.168.0.166"
    localPort   = 20001
    bufferSize  = 1024 

    CLIENT= "192.168.0.127"

    msgFromServer       = "Hello UDP Client"
    bytesToSend         = str.encode(msgFromServer)

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Bind to address and ip
    UDPServerSocket.bind((localIP, localPort))

    logging.info("Thread %s: UDP server up and listening", name)

    got_address = False

    # Listen for incoming datagrams
    while(True):

        if not (got_address):
            bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
            # message = bytesAddressPair[0]
            address = bytesAddressPair[1]
            print(address)
            got_address = True

        logging.info("Thread %s: Sending UDP data to client", name)
        
        # Sending a reply to client
        UDPServerSocket.sendto(shared_data.udp_data, address)
        # time.sleep(0.0005)