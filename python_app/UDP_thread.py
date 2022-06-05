import threading
import logging
import socket


from TCP_thread import TCP_Thread

LOCALIP             = "192.168.0.166"
UDP_STREAM_PER_MS   = 5
CLEANUP_PER_MS      = 10000

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

            # try:
            safe_client_dict = shared_data.client_dict.dict_get_dict()
            # Sending data to client
            for client in safe_client_dict:
                if(shared_data.millis() - safe_client_dict[client] > CLEANUP_PER_MS):
                    remove_list.append(client)
                else:
                    UDPServerSocket.sendto(shared_data.udp_data.read_data(), client)
            
            # Cleanup
            for client in remove_list:
                logging.info("Thread %s: Removing client (%s:%d) from the list",name,client[0],client[1])
                shared_data.client_dict.dict_pop_data(client)

            # except Exception as e:
            #     logging.error("Thread %s: Error accessing client list... error %s",name,e)


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
            if not (address in shared_data.client_dict.dict_get_dict()):
                logging.info("Thread %s: Adding client (%s:%d) to list",name,address[0],address[1])
                shared_data.num_threads.mutex.acquire()
                shared_data.num_threads.data += 1
                shared_data.num_threads.mutex.release()
                
                logging.info("Thread %s: Creating TCP thread",name)
                ThreadID = shared_data.num_threads.read_data()+1
                tcp_t = threading.Thread(target=TCP_Thread, args=(ThreadID,shared_data,address[0]))
                logging.info("Thread %s: Forking TCP thread with id %d",name,ThreadID)
                tcp_t.start()
                shared_data.num_threads.write_data(ThreadID)
            else:
                logging.debug("Thread %s: Client (%s:%d) already in list",name,address[0],address[1])
            
            shared_data.client_dict.dict_write_data(address,shared_data.millis())

        except Exception as e:
            logging.error("Thread %s: Error accessing client list... error %s",name,e)
