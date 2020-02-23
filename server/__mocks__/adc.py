from spidev import SpiDev
from time import sleep
 
class MCP3008:
    def __init__(self, bus=0, device=0, max_speed_hz=1000000):
        self.spi = SpiDev()
        self.spi.open(bus, device)
        self.spi.max_speed_hz = max_speed_hz
    
    def read(self, channel=0):
        adc = self.spi.xfer2([1, (8 + channel) << 4, 0])
        data = ((adc[1] & 3) << 8) + adc[2]
        return data
            
    def close(self):
        self.spi.close()

adc = MCP3008()

while True:
    for i in range(8):
        val = adc.read(i)
        print("Channel", i, ": ", val, "Einh. = ", round(val/1023.*3.3,4), "V = ", round(val/10.23,1), "%")
    sleep(1)
    print()
