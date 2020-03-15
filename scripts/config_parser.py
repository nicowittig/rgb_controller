import json

from light_element import Light_Element

with open('config.json') as config_file:
    config = json.load(config_file)

def get_light_elements():
    light_elements = []
    first_pixel = 0

    for le in config["light-elements"]:
        num_pixels = len(le["pixels"])
        light_elements.append(Light_Element(first_pixel, num_pixels, le["brightness"]))
        first_pixel += num_pixels

    num_pixels = first_pixel-1
    return light_elements
