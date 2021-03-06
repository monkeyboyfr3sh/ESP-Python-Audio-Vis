import time
import logging
import socket

TRY_COUNT = 2

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
            for i in range(TRY_COUNT):
                shared_data.led_on_cmd()
        
        elif(keydata == 'off'):
            print()
            for i in range(TRY_COUNT):
                shared_data.led_off_cmd()

        elif(keydata == 'sync'):
            print()
            shared_data.led_sync_cmd()

        elif(keydata == 'rd#'):
            print()
            for i in range(TRY_COUNT):
                shared_data.read_num_led()

        elif(keydata == 'wr#'):
            print()
            for i in range(TRY_COUNT):
                shared_data.write_num_led(100)

        elif(keydata == 'ls clients'):
            safe_client_dict = shared_data.client_dict.dict_get_dict()
            logging.info("Thread %s: Listing client threads", name)
            for client in safe_client_dict:
                logging.info("Thread %s: Client: %s:%d", name,client[0],client[1])
            print()
            
        else:
            logging.info("Thread %s: Can't process KB input", name)

    exit(0)