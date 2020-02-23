from time import sleep

import config
import neopixel
from color import Color
from e_meteor import E_Meteor
from e_rainbow_shift import E_Rainbow_Shift
from e_static_color import E_Static_Color
from e_thermometer import E_Thermometer
from effect import Effect
from input import Input_Analog, Input_Digital, Input_Temperature
from light_element import Light_Element

neoPixels = neopixel.NeoPixel(config.LED_PIN, config.NUM_LEDS)

light_elements = [
    Light_Element(neoPixels, 0, 10, .2)
]

inputs = [
    Input_Analog(0),
    Input_Temperature(trigger_value=25)
]

effects = [
    #E_Static_Color(light_elements[0], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
    #E_Rainbow_Shift(light_elements[0], soft_shift=True, shift_forward=True, invert_colors=False, speed=1),
    #E_Meteor(light_elements[0], color_hue=190, forward=False, trail_decay=60, no_random=False),
    E_Thermometer(light_elements[0], inputs[1], 20, 30, inverted=True)
]

def refresh_inputs():
    for i in inputs:
        i.refresh()

def init_effects():
    for e in effects:
        e.init()

def run_effects():
    for e in effects:
        e.run()

def show_all():
    for le in light_elements:
        le.show()

init_effects()
while True:
    refresh_inputs()
    run_effects()
    show_all()
    #print(inputs[1])
    sleep(.0)
