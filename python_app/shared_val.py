import threading
import time
import math
import binascii

import enum

class Led_Code(enum.Enum):
    OFF            = 0
    ON             = 1
    POS            = 2
    SYNC           = 3
    READ_NUM_LED   = 4
    WRITE_NUM_LED  = 5

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

class DictDataField(DataField):
    def __init__(self,init_data=None,barrier_init=1):
        DataField.__init__(self,init_data=init_data,barrier_init=barrier_init)

    def dict_write_data(self,key,value):
        self.mutex.acquire()
        self.data[key] = value
        self.mutex.release()

    def dict_read_data(self,key):
        self.mutex.acquire()
        read_val = self.data[key]
        self.mutex.release()
        return read_val

    def dict_get_dict(self):
        self.mutex.acquire()
        read_val = dict(self.data)
        self.mutex.release()
        return read_val
    
    def dict_pop_data(self,key):
        self.mutex.acquire()
        pop_val = self.data.pop(key)
        self.mutex.release()
        return pop_val

class SharedData:
    def __init__(self):
        self.tcp_data = DataField(init_data=bytearray(Led_Code.ON.value.to_bytes(1,'little')))
        self.udp_data = DataField(init_data=bytearray(int(0).to_bytes(1,'little')))

        self.sound_data = DataField(init_data=0)

        self.led_sync_signal = DataField(init_data=True)
        self.num_leds = DataField(init_data=124)

        self.client_dict = DictDataField(init_data={})
        self.num_threads = DataField(init_data=0)

    def millis(self):
        return math.floor(time.time() * 1000)
    
    '''
    
    LED Data Operations
        - LED posistion is streamed over UDP

    '''

    def write_led_pos_cmd(self,led_pos):
        try:
            led_bytes = bytearray(Led_Code.POS.value.to_bytes(1,'little'))
            led_bytes.extend(led_pos.to_bytes(4,'little'))
            udp_cmd = led_bytes
            self.udp_data.write_data(udp_cmd)
        except:
            pass
    
    def led_off_cmd(self):
        tcp_cmd = [Led_Code.OFF.value]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    def led_on_cmd(self):
        tcp_cmd = [Led_Code.ON.value]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    def led_sync_cmd(self):
        self.led_sync_signal.write_data(True)
        tcp_cmd = [Led_Code.SYNC.value]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    def read_num_led(self):
        tcp_cmd = [Led_Code.READ_NUM_LED.value]
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    def write_num_led(self,num_leds):
        tcp_cmd = bytearray(Led_Code.WRITE_NUM_LED.value.to_bytes(1,'little'))
        tcp_cmd.extend(num_leds.to_bytes(4,'little'))
        self.tcp_data.write_data(tcp_cmd,inc_barrier=True)

    '''
    
    Sound Data Operations
        - Uses LED write to send data over UDPo

    '''

    def write_sound_data(self,sound_data):
        sound_data = int(sound_data)
        self.sound_data.write_data(sound_data)
        self.write_led_pos_cmd(sound_data)