import time
import logging
import socket

import pyaudio
import wave
import audioop

CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 2
RATE = 44100
p = pyaudio.PyAudio()

def PYAUDIO_Thread(name,shared_data):
    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)
    while(True):
        data = stream.read(CHUNK)
        rms = audioop.rms(data, 2)    # here's where you calculate the volume
        rms = int(rms/25)
        shared_data.write_sound_data(rms)

    stream.stop_stream()
    stream.close()
    p.terminate()