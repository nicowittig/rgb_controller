from color import Color
from controller import Controller
import config_parser
import config2 as config


if __name__ == '__main__':
    '''
    a = {"sc": (Color, (0,255,255))}
    b = a["sc"]
    c = b[0](b[1])
    print(c)
    '''

    controller = Controller(config)
    controller.start()