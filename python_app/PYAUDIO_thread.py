import time
import logging

import pyaudio
import audioop
import numpy as np
from collections import deque
from statistics import mean

def inv_cubed(y):
    y0 = 1 + np.power( (y-1),3 )
    return y0

def sq_root(y):
    y0 = np.sqrt(y)
    return y0

class MyCollection:
    def __init__(self, maxlen):
        self.d = deque(maxlen=maxlen)

    def add(self, new_first_object):
        result = None if len(self.d)==0 else self.d[0]
        self.d.append(new_first_object)
        return result
    
    def get_dequeue(self):
        return self.d

def PYAUDIO_Thread(name,shared_data):

    # Config thread
    CHUNK = 1024
    FORMAT = pyaudio.paInt16
    CHANNELS = 2
    RATE = 44100
    AVRG_PER_MS = 500
    AVRG_WIN_SIZE = 500
    RATIO_COEF = 2
    p = pyaudio.PyAudio()

    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)
    
    print_timestamp_ms = shared_data.millis()
    avrg_timestamp_ms = shared_data.millis()

    long_average_window = MyCollection(AVRG_WIN_SIZE)
    long_average = 0
    ratio = 0

    while(True):
        data = stream.read(CHUNK)
        max = audioop.max(data,2)
        rms = audioop.rms(data, 2)    # here's where you calculate the volume
        avg = audioop.avg(data, 2)    # here's where you calculate the volume
        percent = round(rms/max,2)

        # Sample date at interval
        if(shared_data.millis() - avrg_timestamp_ms > AVRG_PER_MS):
            avrg_timestamp_ms = shared_data.millis()
            long_average_window.add(max)
            long_average = mean(long_average_window.get_dequeue())

        if(percent>0.1):
            try:
                percent = (np.log(sq_root(percent))+1)
                percent = np.abs(np.log(sq_root(percent))+1)
            except:
                pass
            
        if(long_average>0):
            ratio = round(rms/long_average,2)

        # percent = np.floor(inv_cubed(percent)*124).astype('byte')sq_root
        pixels = np.abs((percent*124) * (ratio*RATIO_COEF))
        pixels = np.min((np.floor(pixels),255)).astype('byte')

        # # Print at interval
        # if(shared_data.millis() - print_timestamp_ms > 50):
        #     print_timestamp_ms = shared_data.millis()
        #     print('RMS: {}; MAX: {}; RATIO: {}; Pixels: {}, '.format(rms,max,ratio,pixels))

        shared_data.write_sound_data(pixels)

    stream.stop_stream()
    stream.close()
    p.terminate()