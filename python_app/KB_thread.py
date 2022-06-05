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
            shared_data.led_on_cmd()
        
        elif(keydata == 'off'):
            print()
            shared_data.led_off_cmd()
            shared_data.led_off_cmd()

        elif(keydata == 'sync'):
            print()
            for i in range(3):
                shared_data.led_sync_cmd()

        elif(keydata == 'rd#'):
            print()
            shared_data.read_num_led()

        elif(keydata == 'wr#'):
            print()
            shared_data.write_num_led(100)
            
        else:
            logging.info("Thread %s: Can't process KB input", name)

    exit(0)