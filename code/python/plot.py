# -*- coding: utf-8 -*-
# @Author: obsidian
# @Date:   2016-04-02 20:06:14
# @Last Modified by:   obsidian
# @Last Modified time: 2016-04-03 10:14:48
import numpy as np
import matplotlib.pyplot as plt

front_x = 0
front_y = 1
angle = 2
speed = 3
diserr = 4
angerr = 5
steerang = 6


l = eval('[' + open('path.txt','r').read(-1).replace('}',']').replace('{','[') + ']')
a = np.array(l)
plt.plot(a[:,0] / 10.0,a[:,1] / 10.0,'r')
# plt.show()
f = open('pointpath.c')
lis = eval(f.read(-1).split('=')[1].replace('{','[').replace('}',']').replace('\r','').replace('\n','').replace(';',''))
x = []
y = []
for i in range(len(lis)):
    x.append(lis[i][0][0])
    y.append(lis[i][0][1])
plt.plot(x,y,'b')
mend = []
kp = []
for i in range(len(a)):
	temp = (a[i][diserr]+a[i][angerr]*4.5)/10
	kp_temp = temp/a[i][steerang]
	mend.append(temp)
	kp.append(kp_temp)
# plt.plot(a[:,front_y],a[:,diserr],'b')
# plt.plot(a[:,front_y],a[:,angerr],'r')
plt.plot(a[:,front_y],mend,'g')
plt.plot(a[:,front_y],a[:,steerang],'y')
plt.plot(a[:,front_y],kp,'b')


plt.show()