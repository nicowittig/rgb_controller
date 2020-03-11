import math
from time import time

from color import Color
from effect import Effect


class E_Bouncing_Balls(Effect):
    def __init__(self, light_element, ball_colors):
        super().__init__(light_element, delay=0, name="Bouncing Balls")

        self.__ball_colors = ball_colors
        self.__ball_count = len(ball_colors)

        self.__gravity = -9.81
        self.__start_height = 1

        self.__impact_velocity_start = math.sqrt(-2 * self.__gravity * self.__start_height)

        self.__height = []
        self.__impact_velocity = []
        self.__time_since_last_bounce = []
        self.__position = []
        self.__clock_time_since_last_bounce = []
        self.__damping = []

    def __get_millis(self):
        return round(time() * 1000)

    def init(self):
        for i in range(self.__ball_count):
            self.__height.append(self.__start_height)
            self.__impact_velocity.append(0.0)
            self.__time_since_last_bounce.append(0.0)
            self.__position.append(0)
            self.__clock_time_since_last_bounce.append(self.__get_millis())
            self.__damping.append(0.9 - float(i)/math.pow(self.__ball_count, 2))

        self.set_color(Color((0, 255, 0)))

        return True

    def run(self):
        if self.ready_to_run():
            self.set_color(Color((0, 255, 0)))

            for i in range(self.__ball_count):
                self.__time_since_last_bounce[i] = self.__get_millis() - self.__clock_time_since_last_bounce[i]
                self.__height[i] = 0.5 * self.__gravity * math.pow(self.__time_since_last_bounce[i] / 1000, 2) \
                                 + self.__impact_velocity[i] * self.__time_since_last_bounce[i] / 1000

                if self.__height[i] < 0:
                    self.__height[i] = 0
                    self.__impact_velocity[i] = self.__damping[i] * self.__impact_velocity[i]
                    self.__clock_time_since_last_bounce[i] = self.__get_millis()

                    if self.__impact_velocity[i] < 0.01:
                        self.__impact_velocity[i] = self.__impact_velocity_start

                self.__position[i] = round(self.__height[i] * (self._Effect__light_element.num_pixels - 1) / self.__start_height)
                p = self.__position[i]
                b = self.__ball_colors[i]
                self.set_pixel(self.__position[i], self.__ball_colors[i])

        return False
