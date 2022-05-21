import socket
import time
import logging
import threading
import sys
from tracemalloc import start
import time
import math

import torch
import cv2

from pytorch_models.yolov5 import YoloV5

data_mutex = threading.Semaphore(1)
data_ready = threading.Semaphore(1)
shared_data = [0x05,False]

def millis():
    return math.floor(time.time() * 1000)

def write_shared_data(tcp_cmd):
    # Acquire data rights
    data_mutex.acquire()
    
    # Update data and release tcp thread
    if(shared_data[1]!=tcp_cmd):
        shared_data[1] = tcp_cmd
        data_ready.release()
    
    # Release data rights
    data_mutex.release()
    

def TCP_Thread(name):
    HOST, PORT = "192.168.0.75", 3333

    logging.info("Thread %s: starting", name)

    # Create a socket (SOCK_STREAM means a TCP socket)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        # Connect to server and send data
        sock.connect((HOST, PORT))
        
        while True:
            
            # Stall until new data is written to buffer
            data_ready.acquire()

            logging.info("Thread %s: Sending %d bytes", name,len(bytes(shared_data)))
                
            # sock.sendall(bytes(data + "\n", "utf-8"))
            sock.sendall(bytes(shared_data))
            
            # Receive data from the server and shut down
            received = str(sock.recv(1024), "utf-8")

            time.sleep(0.5)    

def CV_Thread(name):
    CAMERA_INDEX    = 0
    IMG_W           = 1280
    IMG_H           = 720

    # Init and check camera for function
    ret = False
    cap = cv2.VideoCapture(CAMERA_INDEX)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, IMG_W)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, IMG_H)
    if not (cap.isOpened()):
        print("Could not open video device")
    else:
        print("Reading frame from camera... ", end='')
        ret, frame = cap.read()
        if not (ret):
            print("Could not capture frame")
        else:
            print("Captured frame shape:",frame.shape)
            IMG_H,IMG_W = frame.shape[0:2]
            print(IMG_H,IMG_W)

    if not (ret):
        print("Error with video device. Exiting")
        exit(0)

    device = ('cuda' if torch.cuda.is_available() else 'cpu')
    print(device)

    net = YoloV5(device=device)

    person_det_timer = millis()    
    active_timer = False
    det_state = False
    while(ret):
        waitkey = cv2.waitKey(1) & 0xFF
        if waitkey == ord('q'):    
            print("Exiting program")
            break
        
        # Capture frame-by-frame
        ret, frame = cap.read()
        if(net.repo!=None):
            frame = net(frame)

            if(det_state!=net.person_det):
                if not (active_timer):
                    active_timer = True
                    person_det_timer = millis()
                elif(millis()-person_det_timer>500):
                    det_state = net.person_det
                    write_shared_data(det_state)
            else:
                active_timer = False
        
        # Display the frame
        cv2.imshow('Frame', frame)
    
    cap.release()
    cv2.destroyAllWindows()

    exit(0)

def KB_Thread(name):
    
    logging.info("Thread %s: starting", name)

    while(True):
        logging.info("Thread %s: Data send cmd: ", name)
        keydata = input()
        
        if(keydata == '1'):
            logging.info("Thread %s: Sending 'ON' command", name)
            write_shared_data(True)
        elif(keydata == '0'):
            logging.info("Thread %s: Sending 'OFF' command", name)
            write_shared_data(False)
        elif(keydata == 'q'):
            logging.info("Thread %s: Breaking", name)
            break
        
    exit(0)

if __name__ == "__main__":

    format = "%(asctime)s: %(message)s"

    logging.basicConfig(format=format, level=logging.INFO,

                        datefmt="%H:%M:%S")


    logging.info("Main    : Creating TCP thread")
    tcp_t = threading.Thread(target=TCP_Thread, args=(1,))
    logging.info("Main    : Creating CV thread")
    cv_t = threading.Thread(target=CV_Thread, args=(2,))
    logging.info("Main    : Creating KB thread")
    kb_t = threading.Thread(target=KB_Thread, args=(3,))

    logging.info("Main    : Forking TCP thread")
    tcp_t.start()
    logging.info("Main    : Forking CV thread")
    cv_t.start()
    logging.info("Main    : Forking KB thread")
    kb_t.start()

    # logging.info("Main    : Waiting for TCP Thread to finish")
    # x.join()

    logging.info("Main    : all done")