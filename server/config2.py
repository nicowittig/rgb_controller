import board
import neopixel
from color import Color

from e_interactive_spin import E_Interactive_Spin
from e_meteor import E_Meteor
from e_rainbow_shift import E_Rainbow_Shift
from e_static_color import E_Static_Color
from e_thermometer import E_Thermometer

from input import Input_Analog, Input_Digital, Input_Temperature
from light_element import Light_Element

#################
# Board Setting #
#################

board_pin = board.D18

#########
# Flask #
#########

host = "192.168.178.150"
port = 2001
debug = False

#################
# LEDs & Inputs #
#################

brightness = 1.0
light_elements = [
    Light_Element(0, 80, brightness)
]

inputs = [
    Input_Temperature(trigger_value=25)
]

###################
# Modes & Effects #
###################

default_mode = 0

def mode_switch(mode):
    if mode == 0:
        return [
            E_Static_Color(light_elements[0], Color((0,255,0)))
        ]
    elif mode == 1:
        return [
            E_Static_Color(light_elements[0], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True)
        ]
    elif mode == 2:
        return [
            E_Rainbow_Shift(light_elements[0], soft_shift=True, speed=1, delay=50)
        ]
    elif mode == 3:
        return [
            E_Meteor(light_elements[0], color_hue=190, forward=False, trail_decay=60, no_random=False)
        ]
    elif mode == 4:
        return [
            E_Thermometer(light_elements[0], inputs[0], 20, 35, inverted=True)
        ]
    else:
        return [
            E_Static_Color(light_elements[0], Color((0,255,0)))
        ]