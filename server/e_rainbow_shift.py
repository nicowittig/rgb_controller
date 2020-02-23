from color import Color
from effect import Effect


class E_Rainbow_Shift(Effect):
    def __init__(self, light_element, soft_shift=False, shift_forward=True, invert_colors=False, speed=1):
        super().__init__(light_element, "Rainbow Shift")

        self.__soft_shift = soft_shift
        self.__shift_forward = shift_forward
        self.__invert_colors = invert_colors
        self.__speed = abs(speed)

    def init(self):
        if self.__invert_colors:
            super().set_color(Color((255,255,255)), Color((0,255,255)), hue_cycle_forward=False)
        else:
            super().set_color(Color((0,255,255)), Color((255,255,255)), hue_cycle_forward=True)
        return True

    def run(self):
        if self.__soft_shift:
            super().increase_hue(self.__speed if self.__shift_forward else -self.__speed)
        else:
            super().shift(self.__speed if self.__shift_forward else -self.__speed)
        return True
