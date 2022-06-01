from http import client
import time
import logging
import socket

LOCALIP             = "192.168.0.166"
UDP_STREAM_PER_MS   = 5
CLEANUP_PER_MS      = 10000

client_dict = {}

def UDP_Streaming_Thread(name,shared_data):
    
    # Config thread 
    PORT = 20002
    BUFFERSIZE  = 1024

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)
    UDPServerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    UDPServerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    # Bind to address and ip
    UDPServerSocket.bind((LOCALIP, PORT))

    logging.info("Thread %s: UDP server up and broadcasting", name)

    # Timers
    udp_timestamp_ms = shared_data.millis()

    while(True):

        # Broadcast to clients
        if(shared_data.millis()-udp_timestamp_ms > UDP_STREAM_PER_MS):
            udp_timestamp_ms = shared_data.millis()

            remove_list = []

            try:
                shared_data.client_list.mutex.acquire()
                # Sending data to client
                for client in client_dict:
                    if(shared_data.millis() - client_dict[client] > CLEANUP_PER_MS):
                        remove_list.append(client)
                    else:
                        UDPServerSocket.sendto(shared_data.udp_data.read_data(), client)
                
                # Cleanup
                for client in remove_list:
                    logging.info("Thread %s: Removing client (%s:%d) from the list",name,client[0],client[1])
                    client_dict.pop(client)

                shared_data.client_list.mutex.release()
            except:
                logging.error("Thread %s: Error accessing client list",name)


def UDP_Listening_Thread(name,shared_data):
    
    # Config thread 
    PORT = 20001
    BUFFERSIZE  = 1024

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)
    UDPServerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    UDPServerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    # Bind to address and ip
    UDPServerSocket.bind((LOCALIP, PORT))

    logging.info("Thread %s: UDP server up and listening", name)

    # Listen for incoming datagrams
    while(True):

        logging.debug("Thread %s: Waiting for client", name)
        bytesAddressPair = UDPServerSocket.recvfrom(BUFFERSIZE)
        # message = bytesAddressPair[0]
        address = bytesAddressPair[1]

        try:
            shared_data.client_list.mutex.acquire()
            if not (address in client_dict):
                logging.info("Thread %s: Adding client (%s:%d) to list",name,address[0],address[1])
            else:
                logging.debug("Thread %s: Client (%s:%d) already in list",name,address[0],address[1])
            
            client_dict[address] = shared_data.millis()
            shared_data.client_list.mutex.release()
        except:
            logging.error("Thread %s: Error accessing client list",name)