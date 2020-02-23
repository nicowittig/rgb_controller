import plotext.plot as plx
import numpy as np

l=10
x=np.arange(0, l)
y=np.sin(4*np.pi/l*np.array(x))*np.exp(-0.5*np.pi/l*x)

plx.scatter(x, y, rows=20, cols=100, equations=True, point_color='blue')
plx.show(clear=0)