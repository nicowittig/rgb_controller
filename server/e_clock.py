import math
from time import time, ctime

from color import Color
from effect import Effect


class E_Clock(Effect):
    def __init__(self, light_element, start_color, end_color=None, hue_cycle_forward=None, cycles=1, forward_only=True, time_diff=30, index_pixel=0, show_time_range=True, reverse=False):
        super().__init__(light_element, delay=0, name="Clock")

        self.__start_color = start_color
        self.__end_color = end_color
        self.__hue_cycle_forward = hue_cycle_forward
        self.__cycles = cycles
        self.__forward_only = forward_only

        self.__time_diff = time_diff
        self.__index_pixel = index_pixel
        self.__show_time_range = show_time_range
        self.__reverse = reverse

        self.__seconds_per_led = self._Effect__light_element.num_pixels / time_diff

    def init(self):
        self.set_color(self.__start_color, self.__end_color, self.__hue_cycle_forward, 0, None, self.__cycles, self.__forward_only)
        return True

    def run(self):
        if self.ready_to_run():
            self.set_val(0)

            pixels = math.ceil((time() % self.__time_diff) * self.__seconds_per_led)
            #print(ctime(time()), round(time() % self.__time_diff), pixels, round(self.__seconds_per_led))

            if self.__show_time_range:
                for i in range(pixels):
                    if not self.__reverse:
                        pixel = (self.__index_pixel + i) % self._Effect__light_element.num_pixels
                    else:
                        pixel = (self.__index_pixel - i - 1) % self._Effect__light_element.num_pixels
                    self.set_pixel_val(pixel, 255)
            else:
                if not self.__reverse:
                    pixel = (self.__index_pixel + pixels) % self._Effect__light_element.num_pixels
                else:
                    pixel = (self.__index_pixel - pixels - 1) % self._Effect__light_element.num_pixels
                self.set_pixel_val(pixel, 255)

        return False
