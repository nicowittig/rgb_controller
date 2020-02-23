import board
import neopixel
import colorsys

pixels = neopixel.NeoPixel(board.D18, 30)

def hsv2rgb(hsv):
    rgb_float = colorsys.hsv_to_rgb((hsv[0]%256)/255, (hsv[1]%256)/255, (hsv[2]%256)/255)
    rgb = (int(rgb_float[0]*255)%256, int(rgb_float[1]*255)%256, int(rgb_float[2]*255)%256)
    return rgb

h = 0
while True:
    h += 1
    pixels.fill(hsv2rgb((h, 255, 255)))
 
'''
from rpi_ws281x import *

# LED strip configuration:
LED_COUNT      = 10      # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (18 uses PWM!).
#LED_PIN        = 10      # GPIO pin connected to the pixels (10 uses SPI /dev/spidev0.0).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0       # set to '1' for GPIOs 13, 19, 41, 45 or 53

strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ,LED_DMA,LED_INVERT,LED_BRIGHTNESS,LED_CHANNEL)
strip.begin()

for x in range(0,LED_COUNT):
    strip.setPixelColor(x, Color(255,x*10,0))

strip.show()
'''