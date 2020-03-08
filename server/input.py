import os
import sys

from RPi import GPIO
from spidev import SpiDev


class Input(object):
    def __init__(self, invert):
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
        return None

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
        return "INPUT-- - OUT: " + str(self.digital_read()) + " inv: " + str(self.__invert)


class Input_Digital(Input):
    def __init__(self, input_pin, pull_up=False, invert=False):
        super().__init__(invert)

        self.__input_pin = input_pin
        self.__pull_up = pull_up
        self.__invert = invert

        # use GPIO (not Board) pin names
        GPIO.setmode(GPIO.BCM)

        if pull_up:
            GPIO.setup(input_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        else:
            GPIO.setup(input_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

    def digital_read(self):
        return (GPIO.input(self.__input_pin) == GPIO.HIGH) != self.__invert

    def __str__(self):
        states = (super().is_pushed(), super().is_toggled(), super().is_tapped(), super().is_changed())
        return "INPUT-D - OUT: " + str(self.digital_read()) + " \tstates: " + str(states) + " pin: " + str(self.__input_pin) + " pull-up: " + str(self.__pull_up) + " inv: " + str(self.__invert)


class Input_Analog(Input):
    def __init__(self, adc_channel, adc_bus=0, adc_device=0, adc_max_speed_hz=1000000, trigger_value=None, trigger_adjustment_duration=100, trigger_adjustment_tolerance=.03, trigger_adjustment_absolute=False, invert=True):
        super().__init__(invert)

        self.__adc_channel = adc_channel
        self.__trigger_value = trigger_value
        self.__trigger_adjustment_duration = trigger_adjustment_duration
        self.__trigger_adjustment_tolerance = trigger_adjustment_tolerance
        self.__trigger_adjustment_absolute = trigger_adjustment_absolute
        self.__invert = invert

        # MCP3008
        self.__spi = SpiDev()
        self.__spi.open(adc_bus, adc_device)
        self.__spi.max_speed_hz = adc_max_speed_hz

        if not trigger_value:
            self.adjust_trigger_value()

    def adjust_trigger_value(self):
        min_value = sys.maxsize

        # find min value of analog data
        for i in range(self.__trigger_adjustment_duration):
            ar = self.analog_read()
            if ar < min_value:
                min_value = ar

        # adjust the trigger value according to min value and tolerance
        if self.__trigger_adjustment_absolute:
            self.__trigger_value = min_value - self.__trigger_adjustment_tolerance
        else:
            self.__trigger_value = min_value * (1-self.__trigger_adjustment_tolerance)

    def analog_read(self):
        adc = self.__spi.xfer2([1, (8 + self.__adc_channel) << 4, 0])
        data = ((adc[1] & 3) << 8) + adc[2]
        return data
    
    def digital_read(self):
        return (self.analog_read() >= self.__trigger_value) != self.__invert

    def __str__(self):
        states = (super().is_pushed(), super().is_toggled(), super().is_tapped(), super().is_changed())
        trigger = (round(self.__trigger_value, 1), self.__trigger_adjustment_duration, self.__trigger_adjustment_tolerance)
        return "INPUT-A - OUT: " + str(self.analog_read()) + "->" + str(self.digital_read()) + " \tstates: " + str(states) + " \ttr: " + str(trigger) + " channel: " + str(self.__adc_channel) + " inv: " + str(self.__invert)

class Input_Temperature(Input):
    def __init__(self, invert=False, trigger_value=1):
        super().__init__(invert)

        self.__invert = invert
        self.__trigger_value = trigger_value
        self.__sensor = self.__get_sensor()

    def __get_sensor(self):
        sensor = None
        for i in os.listdir('/sys/bus/w1/devices'):
            if i != 'w1_bus_master1':
                sensor = i
                break
        return sensor

    def analog_read(self):
        tfile = open('/sys/bus/w1/devices/' + self.__sensor + '/w1_slave')
        text = tfile.read()
        tfile.close()
        secondline = text.split("\n")[1]
        temperaturedata = secondline.split(" ")[9]
        temperature = float(temperaturedata[2:]) / 1000
        return temperature

    def digital_read(self):
        return (self.analog_read() >= self.__trigger_value) != self.__invert

    def __str__(self):
        states = (super().is_pushed(), super().is_toggled(), super().is_tapped(), super().is_changed())
        return "INPUT-T - OUT: " + str(self.analog_read()) + "->" + str(self.digital_read()) + " \tstates: " + str(states) + " \ttr: " + str(self.__trigger_value) + " inv: " + str(self.__invert)