from color import Color

from e_bouncing_balls import E_Bouncing_Balls
from e_clock import E_Clock
from e_fire import E_Fire
from e_meteor import E_Meteor
from e_rainbow_shift import E_Rainbow_Shift
from e_static_color import E_Static_Color

from light_element import Light_Element
from dummy import Input, Input_Temperature

#################
# Board Setting #
#################

emulator = True
board_pin = None

#################
# LEDs & Inputs #
#################

brightness = 1
light_elements = [Light_Element(0, 50, brightness)]

inputs = []

###################
# Modes & Effects #
###################

default_mode = 2

def mode_switch(mode):
    if mode == 0:
        return [E_Bouncing_Balls(light_elements[0], [Color((0, 255, 255)), Color((100, 255, 255)), Color((200, 255, 255))])]
    elif mode == 1:
        return [E_Static_Color(light_elements[0], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=2, forward_only=False, increase_hue=1, shift=0, input=None)]
    elif mode == 2:
        return [E_Rainbow_Shift(light_elements[0], soft_shift=True, speed=1, delay=50)]
    elif mode == 3:
        return [E_Clock(light_elements[0], Color((0,255,255)), Color((0,255,255)), time_diff=30, index_pixel=0, show_time_range=True, reverse=False)]
    elif mode == 4:
        return [E_Meteor(light_elements[0], color_hue=190, forward=False, trail_decay=60, no_random=False)]
    elif mode == 5:
        return [E_Fire(light_elements[0], 35, 120)]
    else:
        return [E_Static_Color(light_elements[0], Color((0,255,0)))]

#######
# API #
#######

api_host = "0.0.0.0"
api_port = 2001
api_debug = True

init_json = {
    "system": {},
    "switches": {
        "api": "general",
        "elements": []
    },
    "general": {
        "api": "general",
        "brightness": brightness,
        "elements": []
    },
    "modes": {
        "api": "mode",
        "elements": []
    },
    "inputs": {
        "api": "input",
        "elements": [],
        "elements2": [{"id": i, "key": i, "name": "Input " + str(i)} for i in range(len(inputs)) if not isinstance(inputs[i], Input_Temperature)]
    }
}