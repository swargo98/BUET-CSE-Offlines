# -*- coding: utf-8 -*-
"""
Created on Wed Aug 28 01:47:05 2019

@author: Rasman Swargo
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def dydx(x,y):
    return (x+20*y)*np.sin(x*y)

def SOrderRKMethod(XBeg, XEnd, dydx, step, x,y,y0, a2):
    x=np.arange(XBeg, XEnd, step)
    y.clear()
    y.append(y0)
    a1=1-a2
    it=0
    k=int((XEnd-XBeg)/step)
    for j in range(k-1):
        k1=dydx(x[it],y[it])
        if(a2 == 0.5):
            k2 = dydx(x[it] + step, y[it] + k1 * step)
        elif(a2 == 1):
            k2 = dydx(x[it] + 0.5 * step, y[it] + 0.5 * k1 * step)
        else:
            k2 = dydx(x[it] + (3 / 4) * step, y[it] + (3 / 4) * k1 * step)
        y.append(y[it]+((a1*k1+a2*k2)*step))
        it=it+1
    

def EulerMethod(XBeg, XEnd, dydx, step, x,y,y0):
    #x=np.arange(XBeg, XEnd, step)
    y.clear()
    y.append(y0)
    it=0
    k=int((XEnd-XBeg)/step)
    for j in range(k-1):
        y.append(y[it]+dydx(x[it],y[it])*step)
        it+=1
    
        
def FthOrderRKMethod(XBeg, XEnd, dydx, step, x,y,y0):
    x=np.arange(XBeg, XEnd, step)
    y.clear()
    y.append(y0)
    it=0
    k=int((XEnd-XBeg)/step)
    for j in range(k-1):
        k1=dydx(x[it],y[it])
        k2=dydx(x[it]+step/2,y[it]+k1*step/2)
        k3=dydx(x[it]+step/2,y[it]+k2*step/2)
        k4=dydx(x[it]+step,y[it]+k3*step)
        y.append(y[it]+((k1+2*k2+2*k3+k4)*step)*(1/6))
        it=it+1
        

XBeg=0
XEnd=10
y0=4
steps=[0.01, 0.05, 0.1, 0.5]
colors=['blue', 'red', 'yellow', 'green']
labels=['Step size= 0.01', 'Step size= 0.05', 'Step size= 0.1', 'Step size= 0.5']
x=[]
y=[]

plt.figure(1)
plt.figure(figsize=(10,10))
plt.grid()
it=0
for i in steps:
    x=np.arange(XBeg, XEnd, i)
    EulerMethod(XBeg, XEnd, dydx, i, x,y,y0)
    #print(x)
    plt.plot(x,y,color=colors[it], linewidth=3, label=labels[it])
    plt.title('Euler Method in Different Step Sizes')
    plt.xlabel('x')
    plt.ylabel('y')
    it=it+1
    plt.legend(loc='upper left')

    
plt.figure(2)
plt.figure(figsize=(10,10))
plt.grid()
it=0 
for i in steps:
    x=np.arange(XBeg, XEnd, i)
    SOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0, 0.5)
    #HeunsMethod(XBeg, XEnd, dydx, i, x,y,y0)
    #print(x)
    plt.plot(x,y,color=colors[it], linewidth=3, label=labels[it])
    plt.title('Heuns Method in Different Step Sizes')
    plt.xlabel('x')
    plt.ylabel('y')
    it=it+1
    plt.legend(loc='best')
    
plt.figure(3)
plt.figure(figsize=(10,10))
plt.grid()
it=0     
for i in steps:
    x=np.arange(XBeg, XEnd, i)
    SOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0, 1)
    #MidpointMethod(XBeg, XEnd, dydx, i, x,y,y0)
    #print(x)
    plt.plot(x,y,color=colors[it], linewidth=3, label=labels[it])
    plt.title('Midpoint Method in Different Step Sizes')
    plt.xlabel('x')
    plt.ylabel('y')
    it=it+1
    plt.legend(loc='best')
    
plt.figure(4)
plt.figure(figsize=(10,10))
plt.grid()
it=0     
for i in steps:
    x=np.arange(XBeg, XEnd, i)
    SOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0, 2/3)
    #RaltsonsMethod(XBeg, XEnd, dydx, i, x,y,y0)
    #print(x)
    plt.plot(x,y,color=colors[it], linewidth=3, label=labels[it])
    plt.title('Raltsons Method in Different Step Sizes')
    plt.xlabel('x')
    plt.ylabel('y')
    it=it+1
    plt.legend(loc='best')
    
plt.figure(5)
plt.figure(figsize=(10,10))
plt.grid()
it=0     
for i in steps:
    x=np.arange(XBeg, XEnd, i)
    FthOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0)
    #print(x)
    plt.plot(x,y,color=colors[it], linewidth=3, label=labels[it])
    plt.title('Fourth Order RK Method in Different Step Sizes')
    plt.xlabel('x')
    plt.ylabel('y')
    it=it+1
    plt.legend(loc='best')

Mlabels=['Euler Method', 'Heuns Method', 'Midpoint Method', 'Raltsons Method', 'Fouth Order RK Method']
Mcolors=['blue', 'red', 'yellow', 'green', 'violet']
it=0
for i in steps:
    k='Step Size= '+ str(i)
    x=np.arange(XBeg, XEnd, i)
    plt.figure(it+6)
    plt.figure(figsize=(10,10))
    plt.grid()
    
    EulerMethod(XBeg, XEnd, dydx, i, x,y,y0)
    plt.plot(x,y,color=Mcolors[0], linewidth=3, label=Mlabels[0])
    
    #HeunsMethod(XBeg, XEnd, dydx, i, x,y,y0)
    SOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0, 0.5)
    plt.plot(x,y,color=Mcolors[1], linewidth=3, label=Mlabels[1])
    
    #MidpointMethod(XBeg, XEnd, dydx, i, x,y,y0)
    SOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0, 1)
    plt.plot(x,y,color=Mcolors[2], linewidth=3, label=Mlabels[2])
    
    #RaltsonsMethod(XBeg, XEnd, dydx, i, x,y,y0)
    SOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0, 2/3)
    plt.plot(x,y,color=Mcolors[3], linewidth=3, label=Mlabels[3])
    
    FthOrderRKMethod(XBeg, XEnd, dydx, i, x,y,y0)
    plt.plot(x,y,color=Mcolors[4], linewidth=3, label=Mlabels[4])
    
    plt.title(k)
    plt.xlabel('x')
    plt.ylabel('y')
    it=it+1
    plt.legend(loc='best')