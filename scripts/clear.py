import board
import neopixel

pixels = neopixel.NeoPixel(board.D18, 200)
pixels.fill((0, 0, 0))