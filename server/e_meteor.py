import random

from color import Color
from effect import Effect


class E_Meteor(Effect):
    def __init__(self, light_element, color_hue=190, forward=True, trail_decay=60, no_random=False):
        super().__init__(light_element, "Meteor")

        self.__color_hue = color_hue
        self.__forward = forward
        self.__trail_decay = abs(trail_decay)
        self.__no_random = no_random

        self.__meteor_position = 0

    def init(self):
        super().set_color(Color((self.__color_hue, 255, 0)))
        return True

    def run(self):
        num_pixels = self._Effect__light_element.num_pixels
        self.__meteor_position %= num_pixels

        # fade out the trail
        for i in range(0, num_pixels):
            if self.__no_random or random.randrange(10) >= 5:
                super().get_pixel(i).val = super()._Effect__fade_var(super().get_pixel(i).val, 0, -self.__trail_decay)[1]

        # meteor with full brightness
        super().get_pixel(self.__meteor_position).val = 255
        # move meteor
        self.__meteor_position += 1 if self.__forward else -1

        return True
