import time
import logging
import socket

def KB_Thread(name,shared_data):
    
    logging.info("Thread %s: starting", name)

    while(True):
        logging.info("Thread %s: Reading KB input", name)
        keydata = input("Data to send: ")

        keydata = keydata.lower()
        if(keydata == 'q'):
            logging.info("Thread %s: Breaking", name)
            break

        elif(keydata == 'on'):
            print()
            shared_data.led_on_cmd()
        
        elif(keydata == 'off'):
            print()
            shared_data.led_off_cmd()

        elif(keydata.isdigit()):
            print()
            int_keydata = int(keydata)
            logging.info("Thread %s: Sending '%d' as led pos", name,int_keydata)
            shared_data.write_led_pos_cmd(int_keydata)
        else:
            logging.info("Thread %s: Can't process KB input", name)
    KB_active = False
    exit(0)