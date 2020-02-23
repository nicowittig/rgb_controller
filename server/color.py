import colorsys


def hsv_to_rgb(hsv):
        rgb_float = colorsys.hsv_to_rgb((hsv[0]%256)/255, (hsv[1]%256)/255, (hsv[2]%256)/255)
        rgb = [int(rgb_float[0]*255)%256, int(rgb_float[1]*255)%256, int(rgb_float[2]*255)%256]
        return rgb

def rgb_to_hsv(rgb):
    hsv_float = colorsys.rgb_to_hsv((rgb[0]%256)/255, (rgb[1]%256)/255, (rgb[2]%256)/255)
    hsv = [int(hsv_float[0]*255)%256, int(hsv_float[1]*255)%256, int(hsv_float[2]*255)%256]
    return hsv

class Color(object):
    def __init__(self, hsv=None, rgb=None):
        super().__init__()
        
        if hsv:
            self.__hsv = [hsv[0], hsv[1], hsv[2]]
            self.__rgb = hsv_to_rgb(self.__hsv)
        elif rgb:
            self.__rgb = [rgb[0], rgb[1], rgb[2]]
            self.__hsv = rgb_to_hsv(self.rgb)
        else:
            self.__hsv = [0, 0, 0]
            self.__rgb = [0, 0, 0]

    def __getHSV(self):
        return self.__hsv

    def __setHSV(self, hsv):
        self.__hsv = hsv
        self.__rgb = hsv_to_rgb(self.__hsv)

    def __getRGB(self):
        return self.__rgb

    def __setRGB(self, rgb):
        self.__rgb = rgb
        self.__hsv = rgb_to_hsv(self.__rgb)

    def __getH(self):
        return self.__hsv[0]

    def __setH(self, h):
        self.__hsv[0] = h
        self.__rgb = hsv_to_rgb(self.__hsv)

    def __getS(self):
        return self.__hsv[1]

    def __setS(self, s):
        self.__hsv[1] = s
        self.__rgb = hsv_to_rgb(self.__hsv)

    def __getV(self):
        return self.__hsv[2]

    def __setV(self, v):
        self.__hsv[2] = v
        self.__rgb = hsv_to_rgb(self.__hsv)

    def __getR(self):
        return self.__rgb[0]

    def __setR(self, r):
        self.__rgb[0] = r
        self.__hsv = rgb_to_hsv(self.__rgb)

    def __getG(self):
        return self.__rgb[1]

    def __setG(self, g):
        self.__rgb[1] = g
        self.__hsv = rgb_to_hsv(self.__rgb)

    def __getB(self):
        return self.__rgb[2]

    def __setB(self, b):
        self.__rgb[2] = b
        self.__hsv = rgb_to_hsv(self.__rgb)

    hsv = property(__getHSV, __setHSV)
    rgb = property(__getRGB, __setRGB)

    h = property(__getH, __setH)
    s = property(__getS, __setS)
    v = property(__getV, __setV)
    
    hue = h
    sat = s
    val = v

    r = property(__getR, __setR)
    g = property(__getG, __setG)
    b = property(__getB, __setB)

    red = r
    green = g
    blue = b

    def __eq__(self, value):
        if value == None:
            return False
        return self.hsv == value.hsv

    def __ne__(self, value):
        if value == None:
            return True
        return self.hsv != value.hsv

    def __sub__(self, value):
        return Color(((value.hue - self.hue)%256, (value.sat - self.sat)%256, (value.val - self.val)%256))

    def __add__(self, value):
        return Color(((value.hue + self.hue)%256, (value.sat + self.sat)%256, (value.val + self.val)%256))

    def __mul__(self, value):
        return Color(((value.hue * self.hue)%256, (value.sat * self.sat)%256, (value.val * self.val)%256))

    def __str__(self):
        return "hsv: " + str(self.__hsv) + " rgb: " + str(self.__rgb)