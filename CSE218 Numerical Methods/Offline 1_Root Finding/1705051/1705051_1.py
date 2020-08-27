import numpy as np
import matplotlib.pyplot as plot
import pylab

def ln(x,n):
    sum=0
    prev_term=x
    for i in range (1,n+1,1):
        sum= sum+ prev_term
        prev_term= prev_term*(x)*(-1)*i/(i+1)

    return sum
    


x=input()
n=input()
n=int(n)
x=float(x)
print(ln(x,n))

x=np.arange(-0.9,1.1,0.1)

y=np.log(1+x)
a=ln(x,1)
b=ln(x,3)
c=ln(x,5)
d=ln(x,20)
e=ln(x,50)

fig= plot.figure(figsize=(10,10))
plot.figure(1)
plot.grid()
plot.plot(x,a,color='violet', linewidth=3, label='n=1')
plot.plot(x,b, color='blue', linewidth=3, label='n=3')
plot.plot(x,c, color='green', linewidth=3, label='n=5')
plot.plot(x,d, color='black', linewidth=3, label='n=20')
plot.plot(x,e, color='yellow', linewidth=3, label='n=50')
plot.plot(x,y,color='red', linewidth=3, label='Original Line', linestyle='--')
pylab.legend(loc='upper left')

n=np.arange(2, 51, 1)
RelAppErr=[]
for i in n:
    RAE=1-(ln(.5,i-1)/ln(.5,i))
    if RAE<0 :
        RAE=RAE*(-1)
    '''print(RAE)'''
    RelAppErr.append(RAE)

fig= plot.figure(figsize=(10,10))
plot.figure(2)
plot.grid()
plot.plot(n,RelAppErr, color='blue', linewidth=3)