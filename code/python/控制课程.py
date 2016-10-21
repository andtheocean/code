import numpy as np
import matplotlib.pyplot as plt

# global k = 0.1,kp = 0.1, ki = 0.1, kd = 0.1
# global A = kd + ki + kp
# global B = - (kp + 2 * kd);
# global C = kd;
k = 0.1
kp = 0.1
ki = 0.1
kd = 0.1
A = kd + ki + kp
B = - (kp + 2 * kd);
C = kd;
error = [10,10]
mend = 0
def get_pid( error_now,mend):
        delta = A*error_now + B*error[1]+ C*error[0];
        mend += delta;
        error[0] = error[1]
        error[1] = error_now
        return mend

x = []
y = []
for i in range(11):
    x.append(0.1*i)
    y.append(100)

q = 100 + 10
count = 0
error_q = 10
while((q > 101 or error_q < 99) and count<100 ):
    # x.append(1 + count*0.1)
    x.append(1 + count* 0.1)
    y.append(q)
    count = count + 1
    error_p = 100*0.1 - q*k
    error_q = get_pid(error_p,mend)
    q += error_q
    print(error_q)
print(x)
print(y)
plt.plot(x,y)
plt.show()







