from matplotlib import pyplot as plt
import numpy as np


def x_t(t):
    t = float(t)
    return 0.5 + 0.3*t + 3.9*t*t- 4.7*t*t*t
def y_t(t):
    t = float(t)
    return 1.5 + 0.3 * t + 0.9*t*t -2.7*t*t*t

vals = np.arange(start=0, stop=1, step=0.00001)
x_vals = []
y_vals = []
tstars = []
for e in vals:
    x_vals.append(x_t(e))
    y_vals.append(y_t(e))

f = open("bin/numerical-project/Release/points.txt", "r")
for i in range(42):
    tstars.append(f.readline())
f.close()
xts = []
yts = []
for i in range(21):
    xts.append(tstars[2*i])
    yts.append(tstars[(2*i)+1])

plt.plot(x_vals, y_vals)
for e in tstars:
    plt.plot(x_t(e),y_t(e),'ok')