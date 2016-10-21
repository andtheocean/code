import numpy as np
import matplotlib.pyplot as plt

x = np.arange(-10,10,0.1)
y = []
k = [-10,-2,-1,-0.75,-0.5,0,0.5,1,1.5,2.5,10]

for i in k:
    y = x ** (-i)
    plt.plot(x,y)
    plt.annotate(i,xy = (3,3**(-i)),xytext = (4,3**(-i)+1),arrowprops = dict(arrowstyle = '->'))
plt.annotate(-2,  xy = (2,4), xytext = (3,5), arrowprops = dict(arrowstyle="->"))
plt.annotate(-10, xy = (1.1,2.6), xytext = (2.1,3.6), arrowprops = dict(arrowstyle="->"))
plt.xlim(-10,10)
plt.ylim(-10,10)
z = []
for i in range(200):
    z.append('0')
plt.plot(x,z)
plt.title("y = x ^ (-k)")
plt.show()