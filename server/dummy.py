import os
import sys


class Input(object):
    def __init__(self, invert=False):
        super().__init__()

        # Input Modes:
        # 0 - Push Mode   - 1 if the input is pressed, else false
        # 1 - Toggle Mode - switches between 1 and 0 with every press of the input (release-unlock)
        # 2 - Tap Mode    - 1 if the input is pressed but switches after the call to 0
        # 3 - Change Mode - 1 if the input changes its state and switches after the call to 0

        self.__invert = invert
        self.__state = [False, False, False, False]
        self.__ready_for_next_input = [True, True, True, True]

        self.__external_tap = False

    def digital_read(self):
        return 0

    def external_tap(self):
        self.__external_tap = True
        return None

    def refresh(self):
        val = self.digital_read() or self.__external_tap

        # Push Mode
        self.__state[0] = val

        # Toggle Mode
        if val:
            if self.__ready_for_next_input[1]:
                self.__ready_for_next_input[1] = False
                self.__state[1] = not self.__state[1]
        else:
            self.__ready_for_next_input[1] = True

        # Tap Mode
        if val:
            if self.__ready_for_next_input[2]:
                self.__ready_for_next_input[2] = False
                self.__state[2] = True
        else:
            self.__ready_for_next_input[2] = True
            self.__state[2] = False

        # Change Mode
        if not self.__state[3]:
            if self.__ready_for_next_input[3] != val:
                self.__ready_for_next_input[3] = val
                self.__state[3] = True

        self.__external_tap = False

    def is_pushed(self):
        return self.__state[0]

    def is_toggled(self):
        return self.__state[1]

    def is_tapped(self):
        if self.__state[2]:
            self.__state[2] = False
            return True
        else:
            return False

    def is_changed(self):
        if self.__state[3]:
            self.__state[3] = False
            return True
        else:
            return False

    def __str__(self):
        return "EMU-INPUT--"


class Input_Digital(Input):
    def __init__(self, input_pin, pull_up=False, invert=False):
        super().__init__(invert)

    def digital_read(self):
        return False

    def __str__(self):
        return "EMU-INPUT-D"


class Input_Analog(Input):
    def __init__(self, adc_channel, adc_bus=0, adc_device=0, adc_max_speed_hz=1000000, trigger_value=None, trigger_adjustment_duration=100, trigger_adjustment_tolerance=.03, trigger_adjustment_absolute=False, invert=True):
        super().__init__(invert)

    def analog_read(self):
        return 0
    
    def digital_read(self):
        return False

    def __str__(self):
        return "EMU-INPUT-A"


class Input_Temperature(Input):
    def __init__(self, invert=False, trigger_value=1):
        super().__init__(invert)

    def analog_read(self):
        return 0
    
    def digital_read(self):
        return False

    def __str__(self):
        return "EMU-INPUT-T"


class CPUTemperature():
    temperature = 22
    def __init__(self):
        return None