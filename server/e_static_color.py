from effect import Effect
from input import Input


class E_Static_Color(Effect):
    def __init__(self, light_element, start_color, end_color=None, hue_cycle_forward=None, cycles=1, forward_only=True, increase_hue=0, shift=0, input=None):
        super().__init__(light_element, delay=0, name="Static Color")

        self.__start_color = start_color
        self.__end_color = end_color
        self.__hue_cycle_forward = hue_cycle_forward
        self.__cycles = cycles
        self.__forward_only = forward_only
        self.__increase_hue = increase_hue
        self.__shift = shift
        self.__input = input

    def init(self):
        super().set_color(self.__start_color, self.__end_color, self.__hue_cycle_forward, cycles=self.__cycles, forward_only=self.__forward_only)
        return True

    def run(self):
        if self.__input:
            if self.__input.is_toggled():
                self.increase_hue(self.__increase_hue)
                self.shift(self.__shift)
        else:
            self.increase_hue(self.__increase_hue)
            self.shift(self.__shift)
        return True
