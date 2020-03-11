import board
from color import Color

from e_bouncing_balls import E_Bouncing_Balls
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
    Input_Analog(0)
]

###################
# Modes & Effects #
###################

default_mode = 5

def mode_switch(mode):
    if mode == 0:
        return [E_Static_Color(light_elements[i], Color((0,255,0))) for i in range(len(light_elements))]
    elif mode == 1:
        return [E_Static_Color(light_elements[i], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=2, forward_only=False, increase_hue=1, shift=0, input=inputs[i]) for i in range(len(light_elements) -1 )] \
             + [E_Static_Color(light_elements[6], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=2, forward_only=False, increase_hue=1, shift=1)]
    elif mode == 2:
        return [E_Interactive_Spin(light_elements[i], inputs[i]) for i in range(len(light_elements) - 1)] \
             + [E_Rainbow_Shift(light_elements[6], soft_shift=True, speed=1, delay=50)]
    elif mode == 3:
        return [E_Static_Color(light_elements[i], Color((0,255,0))) for i in range(len(light_elements) - 1)] \
             + [E_Meteor(light_elements[6], color_hue=190, forward=False, trail_decay=60, no_random=False)]
    elif mode == 4:
        return [E_Static_Color(light_elements[i], Color((0,255,0))) for i in range(len(light_elements) - 1)] \
             + [E_Fire(light_elements[6], 55, 120)]
    elif mode == 5:
        return [E_Static_Color(light_elements[i], Color((0,255,0))) for i in range(len(light_elements) - 1)] \
             + [E_Bouncing_Balls(light_elements[6], [Color((0, 255, 255)), Color((100, 255, 255)), Color((200, 255, 255))])]
    else:
        return [E_Static_Color(light_elements[i], Color((0,255,0))) for i in range(len(light_elements))]

#######
# API #
#######

api_host = "192.168.178.150"
api_port = 2001
api_debug = False

init_json = {
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
            { "id": 1, "key": 2, "name": "Interactive Spin" },
            { "id": 2, "key": 3, "name": "Meteor" },
            { "id": 3, "key": 4, "name": "Fire" },
            { "id": 4, "key": 5, "name": "Bouncing Balls" },
        ]
    },
    "inputs": {
        "api": "input",
        "elements": [
            {"id": 0, "key": 0, "name": "Input UL"},
            {"id": 1, "key": 1, "name": "Input UM"},
            {"id": 2, "key": 2, "name": "Input R"},
            {"id": 3, "key": 3, "name": "Input LM"},
            {"id": 4, "key": 4, "name": "Input LL"},
            {"id": 5, "key": 5, "name": "Input M"}
        ],
        "elements2": [{"id": i, "key": i, "name": "Input " + str(i)} for i in range(len(inputs)) if not isinstance(inputs[i], Input_Temperature)]
    }
}