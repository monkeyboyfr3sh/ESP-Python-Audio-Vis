import threading
import time
import math
import binascii

LED_CODE_OFF    = 0
LED_CODE_ON     = 1
LED_CODE_POS    = 2
LED_CODE_SYNC   = 2

class DataField:
    def __init__(self,init_data=None,barrier_init=1):
        self.barrier = threading.Semaphore(barrier_init)
        self.mutex = threading.Semaphore(1)
        self.data = init_data
    
    def barrier_read(self):
        try:
            self.barrier.acquire()
            return self.read_data() # Using safe read function
        except:
            pass

    def read_data(self):
        try:
            # Safe read data
            self.mutex.acquire()
            read_val = self.data
            self.mutex.release()
            return read_val
        except:
            pass

    def write_data(self,indata,inc_barrier=False):
        try:
            # Safe write data
            self.mutex.acquire()
            self.data = indata
            self.barrier.release() if inc_barrier else None
            self.mutex.release()

            return self.data
        except:
            pass

class SharedData:
    def __init__(self):
        self.tcp_data = DataField(init_data=bytearray(LED_CODE_ON.to_bytes(1,'little')))
        self.udp_data = DataField(init_data=bytearray(int(0).to_bytes(1,'little')))
        self.sound_data = DataField(init_data=0)

    def millis(self):
        return math.floor(time.time() * 1000)
    
    '''
    
    LED Data Operations
        - LED posistion is streamed over UDP

    '''

    def write_led_pos_cmd(self,led_pos):
        try:
            led_bytes = bytearray(LED_CODE_POS.to_bytes(1,'little'))
            led_bytes.extend(led_pos.to_bytes(4,'little'))
            udp_cmd = led_bytes
            self.udp_data.write_data(udp_cmd)
        except:
            pass
    
    def led_off_cmd(self):
        tcp_cmd = [LED_CODE_OFF]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    def led_on_cmd(self):
        tcp_cmd = [LED_CODE_ON]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    def led_sync_cmd(self):
        tcp_cmd = [LED_CODE_ON]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    '''
    
    Sound Data Operations
        - Uses LED write to send data over UDPo

    '''

    def write_sound_data(self,sound_data):
        sound_data = int(sound_data)
        self.sound_data.write_data(sound_data)
        self.write_led_pos_cmd(sound_data)