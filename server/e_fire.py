import random

from color import Color
from effect import Effect


class E_Fire(Effect):
    def __init__(self, light_element, cooling, sparking):
        super().__init__(light_element, delay=0, name="Fire")

        self.__cooling = cooling
        self.__sparking = sparking

        self.__heat = []
        for i in range(self._Effect__light_element.num_pixels):
            self.__heat.append(0)

    def init(self):
        super().set_color(Color((0, 255, 0)))
        return True

    def run(self):
        if self.ready_to_run():

            # Step 1.  Cool down every cell a little
            for i in range(len(self.__heat)):
                cooldown = random.randrange(5, round(((self.__cooling * 10) / self._Effect__light_element.num_pixels) + 2))
                self.__heat[i] = 0 if cooldown > self.__heat[i] else (self.__heat[i] - cooldown) % 256

            # Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for i in range(self._Effect__light_element.num_pixels - 1, 1, -1):
                self.__heat[i] = ((self.__heat[i-1] + 2*self.__heat[i-2]) / 3) % 256

            # Step 3.  Randomly ignite new 'sparks' near the bottom
            if random.randrange(255) < self.__sparking:
                y = random.randrange(7)
                self.__heat[y] = (self.__heat[y] + random.randrange(160, 255)) %256

            # Step 4.  Convert heat to LED colors
            for i in range(self._Effect__light_element.num_pixels):
                self.__set_pixel_heat_color(i, self.__heat[i])

        return True

    def __set_pixel_heat_color(self, pixel, temperature):
        # Scale 'heat' down from 0-255 to 0-191
        t192 = abs(round((temperature/255) * 191))

        heatramp = t192 & 0x3F # 0..63
        heatramp <<= 2 # scale up to 0..255

        # figure out which third of the spectrum we're in
        if t192 > 0x80:
            self.set_pixel(pixel, Color(rgb=(255, 255, heatramp)))
        elif t192 > 0x40:
            self.set_pixel(pixel, Color(rgb=(255, heatramp, 0)))
        else:
            self.set_pixel(pixel, Color(rgb=(heatramp, 0, 0)))
