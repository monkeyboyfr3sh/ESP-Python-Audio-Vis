import threading
import time
import math

LED_CODE_OFF    = 0
LED_CODE_ON     = 1
LED_CODE_POS    = 2

class SharedData:
    def __init__(self):
        self.tcp_barrier = threading.Semaphore(1)

        self.tcp_mutex =    threading.Semaphore(1)
        self.tcp_data =     bytearray(LED_CODE_OFF.to_bytes(1,'little'))

        self.udp_mutex =    threading.Semaphore(1)
        self.udp_data =     bytearray(int(0).to_bytes(1,'little'))

        self.sound_mutex = threading.Semaphore(1)
        self.sound_data = 0

    def millis(self):
        return math.floor(time.time() * 1000)

    def write_tcp_data(self,tcp_cmd):
        # Acquire data rights
        self.tcp_mutex.acquire()

        # TODO: Should make some filter to not update with same data
        # Always write data and release barrier
        self.tcp_data = tcp_cmd
        self.tcp_barrier.release()
        
        # Release data rights
        self.tcp_mutex.release()

    def read_tcp_data_barrier(self):
        # Stall until new data is written to buffer
        self.tcp_barrier.acquire()
        return self.tcp_data

    def write_udp_data(self,udp_cmd):
        # Acquire data rights
        self.udp_mutex.acquire()

        self.udp_data = udp_cmd
        
        # Release data rights
        self.udp_mutex.release()

    def read_udp_data(self):
        return self.udp_data


    def write_led_pos_cmd(self,led_pos):
        if(isinstance(led_pos, int)):
            led_bytes = bytearray(LED_CODE_POS.to_bytes(1,'little'))
            led_bytes.extend(led_pos.to_bytes(4,'little'))
            udp_cmd = led_bytes
            # self.write_tcp_data(tcp_cmd)
            self.write_udp_data(udp_cmd)
        else:
            print('Cant resolve position command')
    
    def led_off_cmd(self):
        tcp_cmd = [LED_CODE_OFF]
        self.write_tcp_data(tcp_cmd)

    def led_on_cmd(self):
        tcp_cmd = [LED_CODE_ON]
        self.write_tcp_data(tcp_cmd)

    def write_sound_data(self,sound_data):
        self.sound_mutex.acquire()
        self.sound_data = int(sound_data)
        self.write_led_pos_cmd(int(sound_data))
        self.sound_mutex.release()

    def read_sound_data(self):
        return int(self.sound_data)