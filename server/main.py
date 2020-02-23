import random
from time import sleep

while True:
    print(not not random.getrandbits(1))
    sleep(.5)
