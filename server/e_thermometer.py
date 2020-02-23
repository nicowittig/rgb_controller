from color import Color
from effect import Effect


class E_Thermometer(Effect):
    def __init__(self, light_element, input_temperature, min_temp, max_temp, inverted=False):
        super().__init__(light_element, "Thermometer")

        self.__input_temperature = input_temperature
        self.__min_temp = min_temp
        self.__max_temp = max_temp
        self.__inverted = inverted

    def init(self):
        if not self.__inverted:
            super().set_color(Color((170,255,0)), Color((0,255,0)), False)
        else:
            super().set_color(Color((0,255,0)), Color((170,255,0)), True)
        return True

    def run(self):
        num_pixels = self._Effect__light_element.num_pixels

        temp = self.__input_temperature.analog_read()
        temp_ratio = (temp - self.__min_temp + 1) / (self.__max_temp - self.__min_temp + 1)

        # upper/lower bound
        if temp_ratio > 1:
            temp_ratio = 1
        elif temp_ratio < 0:
            temp_ratio = 0

        if not self.__inverted:
            temp_pixel = int(num_pixels * temp_ratio)

            # show temperature pixels
            for i in range(0, temp_pixel + 1):
                super().get_pixel(i).val = 255

            # hide rest
            for i in range(temp_pixel + 1, num_pixels):
                super().get_pixel(i).val = 0
        else:
            temp_pixel = int(num_pixels * (1 - temp_ratio))

            # hide rest
            for i in range(0, temp_pixel):
                super().get_pixel(i).val = 0

            # show temperature pixels
            for i in range(temp_pixel, num_pixels):
                super().get_pixel(i).val = 255

        return True
