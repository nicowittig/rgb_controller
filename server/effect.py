import sys

from color import Color


class Effect(object):
    def __init__(self, light_element, name="Effect"):
        super().__init__()

        self.__light_element = light_element
        self.__name = name

    def __get_name(self):
        return self.__name

    name = property(__get_name)

    def __str__(self):
        return self.__name + ": " + str(self.__light_element)

    # returns the color of a given pixel
    def get_pixel(self, index):
        return self.__light_element.get_pixel(index)

    # set a certain pixel to a specific color
    def set_pixel(self, index, color):
        self.__light_element.set_pixel(index, color)

    # checks the attached light element if the colors are similar to the given color
    def check_color_matching(self, color, start_pixel=0, end_pixel=None):

        # no end pixel -> set to end of light element
        if not end_pixel:
            end_pixel = self.__light_element.num_pixels-1

        # first pixel after second -> switch
        if start_pixel > end_pixel:
            start_pixel, end_pixel = end_pixel, start_pixel

        for pixel_index in range(start_pixel, end_pixel+1):
            if self.get_pixel(pixel_index) != color:
                return False

        return True

    # HELPER: decide the hue cycle direction depending on used colors (shortest path)
    def __get_hue_cycle_forward(self, start_color, end_color):
        diff_hue = end_color.hue - start_color.hue
        #hue_cycle_forward = (diff_hue > 0 and diff_hue < 128) or (diff_hue < 0 and diff_hue <= -128)
        hue_cycle_forward = (0 < diff_hue < 128) or diff_hue <= -128
        return hue_cycle_forward

    # get the color the pixel would have if the given gradient would be applied
    def __get_pixel_gradient(self, index_pixel, start_color, end_color=None, hue_cycle_forward=None, area_length=None):

        # no end color -> set to start color
        if not end_color:
            end_color = start_color

        # decide the hue cycle direction depending on used colors (shortest path)
        if hue_cycle_forward == None:
            hue_cycle_forward = self.__get_hue_cycle_forward(start_color, end_color)

        area_length = abs(area_length) if area_length else self.__light_element.num_pixels

        diff_sat = (end_color.sat-start_color.sat)/(area_length-1)
        diff_val = (end_color.val-start_color.val)/(area_length-1)

        if hue_cycle_forward:
            diff_hue = ((end_color.hue-start_color.hue)%256)/(area_length-1)
        else:
            diff_hue = -((start_color.hue-end_color.hue)%256)/(area_length-1)

        return Color((
            start_color.hue+index_pixel*diff_hue,
            start_color.sat+index_pixel*diff_sat,
            start_color.val+index_pixel*diff_val
        ))

    # HELPER: set a gradient from the first to the second color on the specified area on the light element
    def __set_color(self, start_color, end_color=None, hue_cycle_forward=None, start_pixel=0, end_pixel=None):

        # no end pixel -> set to end of light element
        if not end_pixel:
            end_pixel = self.__light_element.num_pixels-1

        # only one pixel -> set to start color
        if start_pixel == end_pixel:
            self.set_pixel(start_pixel, start_color)
            return
        # first pixel after second -> switch
        elif start_pixel > end_pixel:
            start_pixel, end_pixel = end_pixel, start_pixel

        area_length = end_pixel-start_pixel+1

        for i in range(area_length):
            current_pixel = start_pixel + i
            self.set_pixel(current_pixel, self.__get_pixel_gradient(i, start_color, end_color, hue_cycle_forward, area_length))

    # set one or multiple gradients from the first to the second color on the specified area on the light element
    def set_color(self, start_color, end_color=None, hue_cycle_forward=None, start_pixel=0, end_pixel=None, cycles=1, forward_only=True):

        # no end color -> set to start color
        if end_color == None:
            end_color = start_color

        # no end pixel -> set to end of light element
        if end_pixel == None:
            end_pixel = self.__light_element.num_pixels-1

        # expect integers
        start_pixel = int(start_pixel)
        end_pixel = int(end_pixel)

        # first pixel after second -> switch
        if start_pixel > end_pixel:
            start_pixel, end_pixel = end_pixel, start_pixel

        # decide the hue cycle direction depending on used colors (shortest path)
        if hue_cycle_forward == None:
            hue_cycle_forward = self.__get_hue_cycle_forward(start_color, end_color)

        area_length = end_pixel-start_pixel+1
        cycle_length = area_length/cycles

        for c in range(cycles):
            if forward_only or c%2 == 0:
                self.__set_color(start_color, end_color, hue_cycle_forward, int(start_pixel+c*cycle_length), int(start_pixel+(c+1)*cycle_length-1))
            else:
                self.__set_color(end_color, start_color, not hue_cycle_forward, int(start_pixel+c*cycle_length), int(start_pixel+(c+1)*cycle_length-1))

    # increase the hue of every pixel of the attached light element by value
    def increase_hue(self, value):
        for p in self.__light_element.pixels:
            p.hue += value

    # shift all pixels of the attached light element by the given direction-value
    def shift(self, direction):
        if direction > 0:

            save_color = self.get_pixel(self.__light_element.num_pixels-1)

            for i in range(self.__light_element.num_pixels-1, 0, -1):
                self.set_pixel(i, self.get_pixel(i-1))
            self.set_pixel(0, save_color)

            self.shift(direction-1)

        elif direction < 0:

            save_color = self.get_pixel(0)

            for i in range(0, self.__light_element.num_pixels-1):
                self.set_pixel(i, self.get_pixel(i+1))
            self.set_pixel(self.__light_element.num_pixels-1, save_color)

            self.shift(direction+1)

        else:
            return

    # shift only the hue-values of all pixels of the attached light element by the given direction-value
    def shift_hue(self, direction):
        if direction > 0:

            save_hue = self.get_pixel(self.__light_element.num_pixels - 1).hue

            for i in range(self.__light_element.num_pixels - 1, 0, -1):
                self.get_pixel(i).hue = self.get_pixel(i - 1).hue
            self.get_pixel(0).hue = save_hue

            self.shift_hue(direction - 1)

        elif direction < 0:

            save_hue = self.get_pixel(0).hue

            for i in range(0, self.__light_element.num_pixels - 1):
                self.get_pixel(i).hue = self.get_pixel(i + 1).hue
            self.get_pixel(self.__light_element.num_pixels - 1).hue = save_hue

            self.shift_hue(direction + 1)

        else:
            return

    # wipe a gradient through the area between one led and another
    def wipe(self, direction, start_color, end_color=None, hue_cycle_forward=None, start_pixel=0, end_pixel=None):

        if direction == 0:
            return True

        # no end pixel -> set to end of light element
        if end_pixel == None:
            end_pixel = self.__light_element.num_pixels-1

        # first pixel after second -> switch
        if start_pixel > end_pixel:
            start_pixel, end_pixel = end_pixel, start_pixel

        area_length = end_pixel - start_pixel + 1
        min_pixel = sys.maxsize
        max_pixel = -sys.maxsize - 1
        done = True

        # get the first (and last) pixel not yet wiped
        for i in range(start_pixel, end_pixel + 1):
            if self.get_pixel(i) != self.__get_pixel_gradient(i, start_color, end_color, hue_cycle_forward, area_length):
                if i < min_pixel:
                    min_pixel = i
                if i < min_pixel:
                    max_pixel = i
                done = False

        # all pixels already wiped
        if done:
            return True

        if direction > 0:
            i = 0
            while i < direction and min_pixel + i <= end_pixel:
                self.set_pixel(min_pixel + i, self.__get_pixel_gradient(min_pixel + i - start_pixel, start_color, end_color, hue_cycle_forward, area_length))
                i += 1
        else:
            i = 0
            while i > direction and max_pixel + i >= start_pixel:
                self.set_pixel(max_pixel + i, self.__get_pixel_gradient(max_pixel + i - start_pixel, start_color, end_color, hue_cycle_forward, area_length))
                i -= 1

        return False

    # HELPER: fade one single parameter to a certain value by the given steps (one step at a time)
    # returns a tuple: goal-value reached (True/False) and the value
    def __fade_var(self, val, end, step):
        diff = (end-val)%256
        if (step == 0 or val == end         # end value already reached -> set to end
        or (step > 0 and diff < step)       # less than one step is neaded -> set to end
        or (step < 0 and diff-256 > step)):
            return (True, end%256)

        val += step

        diff = (end-step)%256
        if ((step > 0 and val > diff and val <= end)   # no next steps needed -> set to end
         or (step < 0 and val < diff and val >= end)):
            return (True, end%256)

        return (False, val%256)

    # HELPER: fade one pixel of the attached light element to a certain color
    def __fade(self, step, new_color, pixel, short_fade=False):
        current_pixel = self.get_pixel(pixel)

        # short fade uses step or -step regarding to the shortest path for hue
        diff_hue = new_color.hue - current_pixel.hue
        pos_step = (abs(diff_hue) <= 128) == (diff_hue >= 0)

        fade_hue = self.__fade_var(current_pixel.hue, new_color.hue, step if not short_fade or pos_step else -step)
        current_pixel.hue = fade_hue[1]

        fade_sat = self.__fade_var(current_pixel.sat, new_color.sat, step if current_pixel.sat <= new_color.sat else -step)
        current_pixel.sat = fade_sat[1]

        fade_val = self.__fade_var(current_pixel.val, new_color.val, step if current_pixel.val <= new_color.val else -step)
        current_pixel.val = fade_val[1]

        return fade_hue[0] and fade_sat[0] and fade_val[0]

    # fade all pixels in an area of the attached light element to a certain color gradient
    def fade(self, step, start_color, end_color=None, hue_cycle_forward=None, start_pixel=0, end_pixel=None, short_fade=False):

        # no end pixel -> set to end of light element
        if end_pixel == None:
            end_pixel = self.__light_element.num_pixels-1

        area_length = end_pixel - start_pixel + 1
        all_pixels_ready = True

        for i in range(start_pixel, end_pixel + 1):
            if not self.__fade(step, self.__get_pixel_gradient(i - start_pixel, start_color, end_color, hue_cycle_forward, area_length), i, short_fade):
                all_pixels_ready = False

        return all_pixels_ready
