import board
from color import Color

from e_bouncing_balls import E_Bouncing_Balls
from e_clock import E_Clock
from e_fire import E_Fire
from e_interactive_spin import E_Interactive_Spin
from e_meteor import E_Meteor
from e_rainbow_shift import E_Rainbow_Shift
from e_static_color import E_Static_Color
from e_thermometer import E_Thermometer

from input import Input, Input_Analog, Input_Digital, Input_Temperature
from light_element import Light_Element

#################
# Board Setting #
#################

board_pin = board.D18

#################
# LEDs & Inputs #
#################

brightness = 1.0
light_elements = [
    Light_Element(0, 80, brightness)
]

inputs = [
    Input_Temperature(trigger_value=25),
    Input()
]

###################
# Modes & Effects #
###################

default_mode = 1

def mode_switch(mode):
    if mode == 0:
        return [E_Static_Color(light_elements[0], Color((0,255,0)))]
    elif mode == 1:
        return [E_Static_Color(light_elements[0], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=2, forward_only=False, increase_hue=1, shift=0, input=inputs[1])]
    elif mode == 2:
        return [E_Rainbow_Shift(light_elements[0], soft_shift=True, speed=1, delay=50)]
    elif mode == 3:
        return [E_Clock(light_elements[0], Color((0,255,255)), Color((0,255,255)), time_diff=30, index_pixel=0, show_time_range=True, reverse=False)]
    elif mode == 4:
        return [E_Meteor(light_elements[0], color_hue=190, forward=False, trail_decay=60, no_random=False)]
    elif mode == 5:
        return [E_Fire(light_elements[0], 55, 120)]
    elif mode == 6:
        return [E_Bouncing_Balls(light_elements[0], [Color((0, 255, 255)), Color((100, 255, 255)), Color((200, 255, 255))])]
    elif mode == 7:
        return [E_Thermometer(light_elements[0], inputs[0], 20, 35, inverted=True)]
    else:
        return [E_Static_Color(light_elements[0], Color((0,255,0)))]

#######
# API #
#######

api_host = "192.168.1.8"
api_port = 2001
api_debug = False

init_json = {
    "system": {},
    "switches": {
        "api": "general",
        "elements": [
            { "id": 0, "key": "on", "name": "On" },
            { "id": 1, "key": "off", "name": "Off" },
        ]
    },
    "general": {
        "api": "general",
        "brightness": brightness,
        "elements": [
            { "id": 0, "key": "input-all", "name": "Trigger all Inputs" },
            { "id": 1, "key": "input-reset-all", "name": "Reset all Inputs" },
            { "id": 2, "key": "calibrate", "name": "Calibrate Sensors" }
        ]
    },
    "modes": {
        "api": "mode",
        "elements": [
            { "id": 0, "key": 1, "name": "Shifting Color" },
            { "id": 1, "key": 2, "name": "Rainbow Shift" },
            { "id": 2, "key": 3, "name": "Clock" },
            { "id": 3, "key": 4, "name": "Meteor" },
            { "id": 4, "key": 5, "name": "Fire" },
            { "id": 5, "key": 6, "name": "Bouncing Balls" },
            { "id": 6, "key": 7, "name": "Thermometer" },
        ]
    },
    "inputs": {
        "api": "input",
        "elements": [
            {"id": 0, "key": 1, "name": "Input"},
        ],
        "elements2": [{"id": i, "key": i, "name": "Input " + str(i)} for i in range(len(inputs)) if not isinstance(inputs[i], Input_Temperature)]
    }
}