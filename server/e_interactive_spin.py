from color import Color
from effect import Effect

class E_Interactive_Spin(Effect):
    def __init__(self, light_element, input, speed=1, shift_speed=1, min_saturation=0, brightness_gradient=True, delay=80):
        super().__init__(light_element, delay, "Interactive Spin")

        self.__input = input
        self.__speed = speed
        self.__shift_speed = shift_speed
        self.__min_saturation = min_saturation
        self.__brightness_gradient = brightness_gradient

    def init(self):
        if self.__brightness_gradient:
            super().set_color(Color((0,255,255)), Color((0,255,255)), hue_cycle_forward=False, start_pixel=0, end_pixel=0)
            super().set_color(Color((0,255,100)), Color((0,255,10)), hue_cycle_forward=False, start_pixel=1)
        else:
            super().set_color(Color((0,255,255)), Color((0,255,255)), hue_cycle_forward=False)
        return True

    def run(self):
        if self.ready_to_run():

            if self.__input.is_pushed():
                for p in self._Effect__light_element.pixels:
                    p.sat = self.__min_saturation
                    p.val = 255
            if (not self.__input.is_pushed()) and self.__input.is_changed():
                self.init()

            self.increase_hue(self.__speed)

            if self.__brightness_gradient:
                self.shift(self.__shift_speed)

        return True
