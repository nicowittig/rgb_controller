from effect import Effect


class E_Static_Color(Effect):
    def __init__(self, light_element, start_color, end_color=None, hue_cycle_forward=None, cycles=1, forward_only=True):
        super().__init__(light_element, "Static Color")

        self.__start_color = start_color
        self.__end_color = end_color
        self.__hue_cycle_forward = hue_cycle_forward
        self.__cycles = cycles
        self.__forward_only = forward_only

    def init(self):
        super().set_color(self.__start_color, self.__end_color, self.__hue_cycle_forward, cycles=self.__cycles, forward_only=self.__forward_only)
        return True

    def run(self):
        return True
