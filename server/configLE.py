import board
from color import Color

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
    Input(),
    Input_Temperature(trigger_value=25)
]

###################
# Modes & Effects #
###################

default_mode = 1

def mode_switch(mode):
    if mode == 0:
        return [E_Static_Color(light_elements[0], Color((0,255,0)))]
    elif mode == 1:
        return [E_Static_Color(light_elements[0], Color((0,255,255)), Color((170,255,255)), hue_cycle_forward=None, cycles=2, forward_only=False, increase_hue=1, shift=0, input=inputs[0])]
    elif mode == 2:
        return [E_Rainbow_Shift(light_elements[0], soft_shift=True, speed=1, delay=50)]
    elif mode == 3:
        return [E_Meteor(light_elements[0], color_hue=190, forward=False, trail_decay=60, no_random=False)]
    elif mode == 4:
        return [E_Fire(light_elements[6], 55, 120)]
    elif mode == 5:
        return [E_Thermometer(light_elements[0], inputs[0], 20, 35, inverted=True)]
    else:
        return [E_Static_Color(light_elements[0], Color((0,255,0)))]

#######
# API #
#######

host = "192.168.178.150"
port = 2001
debug = False

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
            { "id": 1, "key": 2, "name": "Rainbow Shift" },
            { "id": 2, "key": 3, "name": "Meteor" },
            { "id": 3, "key": 4, "name": "Fire" },
            { "id": 4, "key": 5, "name": "Thermometer" }
        ]
    },
    "inputs": {
        "api": "input",
        "elements": [
            {"id": 0, "key": 0, "name": "Input"},
        ],
        "elements2": [{"id": i, "key": i, "name": "Input " + str(i)} for i in range(len(inputs)) if not isinstance(inputs[i], Input_Temperature)]
    }
}