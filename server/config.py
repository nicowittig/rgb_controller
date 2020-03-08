import board
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
    Light_Element(0, 15, brightness),
    Light_Element(15, 15, brightness),
    Light_Element(30, 15, brightness),
    Light_Element(45, 15, brightness),
    Light_Element(60, 15, brightness),
    Light_Element(75, 15, brightness),
    Light_Element(90, 76, brightness),
]

inputs = [
    Input_Analog(5),
    Input_Analog(4),
    Input_Analog(3),
    Input_Analog(2),
    Input_Analog(1),
    Input_Analog(0),
    Input_Temperature(trigger_value=25)
]

###################
# Modes & Effects #
###################

default_mode = 0

def mode_switch(mode):
    if mode == 0:
        return [
            E_Static_Color(light_elements[0], Color((0,255,0))),
            E_Static_Color(light_elements[1], Color((0,255,0))),
            E_Static_Color(light_elements[2], Color((0,255,0))),
            E_Static_Color(light_elements[3], Color((0,255,0))),
            E_Static_Color(light_elements[4], Color((0,255,0))),
            E_Static_Color(light_elements[5], Color((0,255,0))),
            E_Static_Color(light_elements[6], Color((0,255,0)))
        ]
    elif mode == 1:
        return [
            E_Static_Color(light_elements[0], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
            E_Static_Color(light_elements[1], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
            E_Static_Color(light_elements[2], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
            E_Static_Color(light_elements[3], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
            E_Static_Color(light_elements[4], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
            E_Static_Color(light_elements[5], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True),
            E_Static_Color(light_elements[6], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=1, forward_only=True)
        ]
    elif mode == 2:
        return [
            E_Interactive_Spin(light_elements[0], inputs[0]),
            E_Interactive_Spin(light_elements[1], inputs[1]),
            E_Interactive_Spin(light_elements[2], inputs[2]),
            E_Interactive_Spin(light_elements[3], inputs[3]),
            E_Interactive_Spin(light_elements[4], inputs[4]),
            E_Interactive_Spin(light_elements[5], inputs[5]),
            E_Rainbow_Shift(light_elements[6], soft_shift=True, speed=1, delay=50)
        ]
    elif mode == 3:
        return [
            E_Static_Color(light_elements[0], Color((0,255,0))),
            E_Static_Color(light_elements[1], Color((0,255,0))),
            E_Static_Color(light_elements[2], Color((0,255,0))),
            E_Static_Color(light_elements[3], Color((0,255,0))),
            E_Static_Color(light_elements[4], Color((0,255,0))),
            E_Static_Color(light_elements[5], Color((0,255,0))),
            E_Meteor(light_elements[6], color_hue=190, forward=False, trail_decay=60, no_random=False)
        ]
    elif mode == 4:
        return [
            E_Thermometer(light_elements[6], inputs[6], 20, 30, inverted=True)
        ]
    else:
        return [
            E_Static_Color(light_elements[0], Color((0,255,0))),
            E_Static_Color(light_elements[1], Color((0,255,0))),
            E_Static_Color(light_elements[2], Color((0,255,0))),
            E_Static_Color(light_elements[3], Color((0,255,0))),
            E_Static_Color(light_elements[4], Color((0,255,0))),
            E_Static_Color(light_elements[5], Color((0,255,0))),
            E_Static_Color(light_elements[6], Color((0,255,0)))
        ]
