import time
import logging

import pyaudio
import audioop
import numpy as np

def inv_cubed(y):
    y0 = 1 + np.power( (y-1),3 )
    return y0

def sq_root(y):
    y0 = np.sqrt(y)
    return y0


def PYAUDIO_Thread(name,shared_data):

    # Config thread
    CHUNK = 1024
    FORMAT = pyaudio.paInt16
    CHANNELS = 2
    RATE = 44100
    p = pyaudio.PyAudio()

    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)
    
    print_timestamp_ms = shared_data.millis()

    while(True):
        data = stream.read(CHUNK)
        max = audioop.max(data,2)
        rms = audioop.rms(data, 2)    # here's where you calculate the volume
        percent = round(rms/max,2)
    
        if(percent>0.1):
            percent = np.abs(np.log(sq_root(percent))+1)

        # percent = np.floor(inv_cubed(percent)*124).astype('byte')sq_root
        pixels = np.min((np.floor(percent*124),255)).astype('byte')

        # if(shared_data.millis() - print_timestamp_ms > 50):
        #     print_timestamp_ms = shared_data.millis()
        #     print('RMS: {}; MAX: {}; Pixels: {}, '.format(rms,max,pixels))

        shared_data.write_sound_data(pixels)

    stream.stop_stream()
    stream.close()
    p.terminate()