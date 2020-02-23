from color import Color

class Light_Element(object):
    def __init__(self, neoPixels, first_pixel, num_pixels, brightness=1.0):
        super().__init__()

        self.__neoPixels = neoPixels
        self.__first_pixel = first_pixel
        self.__num_pixels = num_pixels
        self.__brightness = brightness

        self.__pixels = []
        for i in range(self.__num_pixels):
            self.__pixels.append(Color())

    def __get_num_pixels(self):
        return self.__num_pixels

    def __get_brightness(self):
        return self.__brightness

    def __set_brightness(self, brightness):
        self.__brightness = brightness

    def __get_pixels(self):
        return self.__pixels

    def __set_pixels(self, pixels):
        self.__pixels = pixels

    num_pixels = property(__get_num_pixels)
    brightness = property(__get_brightness, __set_brightness)
    pixels = property(__get_pixels, __set_pixels)

    def get_pixel(self, index):
        return self.__pixels[index % self.__num_pixels]

    def set_pixel(self, index, color):
        self.__pixels[index % self.__num_pixels] = color

    def clear(self):
        for p in range(self.__pixels):
            p.hsv = [0, 0, 0]

    def show(self):
        for i in range(self.__num_pixels):
            current_color = Color(self.__pixels[i].hsv)
            current_color.v *= self.__brightness
            self.__neoPixels[self.__first_pixel + i] = tuple(current_color.rgb)

    def __str__(self):
        return "first: " + str(self.__first_pixel) + " num: " + str(self.__num_pixels) + " brightness: " + str(self.__brightness)