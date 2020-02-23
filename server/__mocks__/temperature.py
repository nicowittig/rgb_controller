# ds18b20
import os
from time import sleep

def get_sensor():
    sensor = None
    for i in os.listdir('/sys/bus/w1/devices'):
        if i != 'w1_bus_master1':
            sensor = i
            break
    return sensor

def read(sensor):
    tfile = open('/sys/bus/w1/devices/' + sensor + '/w1_slave')
    text = tfile.read()
    tfile.close()
    secondline = text.split("\n")[1]
    temperaturedata = secondline.split(" ")[9]
    temperature = float(temperaturedata[2:]) / 1000
    return temperature

if __name__ == '__main__':
    sensor = get_sensor()
    while True:
        val = read(sensor)
        if val != None:
            print("Current temperature : %0.3f °C" % val)