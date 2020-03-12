import neopixel
from threading import Thread
from input import Input_Analog, Input_Temperature
from time import time


class Controller(object):
    def __init__(self, config):
        super().__init__()

        self.__active = False

        self.__config = config

        self.__light_elements = config.light_elements
        self.__inputs = config.inputs
        self.__effects = []

        num_pixels = 0
        for le in self.__light_elements:
            num_pixels += le.num_pixels
        self.__neoPixels = neopixel.NeoPixel(config.board_pin, num_pixels)

        self.__mode = config.default_mode
        self.__brightness = config.brightness
        return None

    def start(self):
        if not self.__active:
            self.__active = True

            self.switch_mode(self.__mode)

            t_run_effects = Thread(target=self.run_effects)
            #t_show_all = Thread(target=self.show_all)
            t_refresh_inputs = Thread(target=self.refresh_inputs)
            t_refresh_temperature_inputs = Thread(target=self.refresh_temperture_inputs)

            t_refresh_inputs.start()
            t_refresh_temperature_inputs.start()
            t_run_effects.start()
            #t_show_all.start()

        return None

    def stop(self):
        self.switch_mode(0, discreet=True)
        self.show_all()
        self.__active = False
        return None

    def __run(self):
        while self.__active:
            t_start = round(time()*1000)
            self.run_effects()
            t_stop = round(time()*1000)
            t_diff1 = t_stop - t_start
            print(t_diff1)
        return None

    def switch_mode(self, mode, discreet=False):
        if not discreet:
            self.__mode = mode
        if self.__active:
            self.__effects = self.__config.mode_switch(mode)
            self.init_effects()
        return None

    def external_tap(self, input):
        if self.__active:
            self.__inputs[input].external_tap()
        return None

    def reset_all_inputs(self):
        for i in range(len(self.__inputs)):
            if self.__inputs[i].is_toggled():
                self.external_tap(i)

    def adjust_all_analog_inputs(self):
        for i in self.__inputs:
            if isinstance(i, Input_Analog):
                i.adjust_trigger_value()
        return None

    def refresh_inputs(self):
        while self.__active:
            for i in self.__inputs:
                if not isinstance(i, Input_Temperature):
                    i.refresh()
        return None

    def refresh_temperture_inputs(self):
        while self.__active:
            for i in self.__inputs:
                if isinstance(i, Input_Temperature):
                    i.refresh()
        return None

    def init_effects(self):
        for e in self.__effects:
            e.init()
        return None

    def run_effects(self):
        while self.__active:
            for e in self.__effects:
                e.run()
            self.show_all()
        return None

    def get_brightness(self):
        return self.__brightness

    def set_brightness(self, brightness):
        self.__brightness = brightness
        for le in self.__light_elements:
            le.brightness = brightness

    def show_all(self):
        #while self.__active:
        pixels = []
        for le in self.__light_elements:
            pixels += le.show()
        self.__neoPixels[::] = pixels
        return None
