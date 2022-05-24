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
            shared_data.led_off_cmd()
            break

        elif(keydata == 'on'):
            print()
            shared_data.led_on_cmd()
        
        elif(keydata == 'off'):
            print()
            shared_data.led_off_cmd()

        elif(keydata == 'sync'):
            print()
            shared_data.led_sync_cmd()
            shared_data.led_sync_cmd()

        elif(keydata == '?#'):
            print()
            shared_data.read_num_led()

        else:
            logging.info("Thread %s: Can't process KB input", name)

    exit(0)