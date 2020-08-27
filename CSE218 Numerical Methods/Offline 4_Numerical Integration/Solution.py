# -*- coding: utf-8 -*-
"""
Created on Fri Aug  9 14:53:33 2019

@author: Rasman Swargo
"""

# -*- coding: utf-8 -*-
"""
Created on Fri Aug  9 00:33:30 2019

@author: Rasman Swargo
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches


def trapizoid_rule(x1,x2,fx1,fx2):
    ans=(x2-x1)*(fx2+fx1)/2
    return ans

def one_by_three_rule(x1,x2,x3,fx1,fx2,fx3):
    ans=(x3-x1)*(fx1+fx3+4*fx2)/6
    return ans

def three_by_eight_rule(x1,x2,x3,x4,fx1,fx2,fx3,fx4):
    ans=(x4-x1)*(fx1+3*fx2+3*fx3+fx4)/8
    return ans

def SameIntervalCounter(n,x,sivlen):
    interval=[]
    for i in range(n-1):
        interval.append(x[i+1]-x[i])
    #print(interval)
    #epsilon =np.finfo(float).eps
    #print(epsilon)
    cnt2=0
    crnt=interval[0]
    for i in range(n-1):
        if(abs(crnt-interval[i])<=(0.00001)):
            cnt2+=1
        else:
            sivlen.append(cnt2)
            cnt2=1
            crnt=interval[i]
    sivlen.append(cnt2)
    #print(sivlen.count(1))

def Integration(n,x,fx,sivlen):
    int_sum=0
    x_it=0
    SOTcnt=0
    TRcnt=0
    STEcnt=0
    #print(sivlen)
    for i in sivlen:
        if(i%3==0):
            j=i/3
            for k in range (int(j)):
                int_sum+=three_by_eight_rule(x[x_it+0],x[x_it+1],x[x_it+2],x[x_it+3],fx[x_it+0],fx[x_it+1],fx[x_it+2],fx[x_it+3])
                plt.fill_between(x[x_it+0:x_it+4], fx[x_it+0:x_it+4], color='blue')
                x_it+=3
                STEcnt+=3
        elif(i%2==0):
            j=(i-2)/3
            for k in range (int(j)):
                int_sum+=three_by_eight_rule(x[x_it+0],x[x_it+1],x[x_it+2],x[x_it+3],fx[x_it+0],fx[x_it+1],fx[x_it+2],fx[x_it+3])
                plt.fill_between(x[x_it+0:x_it+4], fx[x_it+0:x_it+4], color='blue')
                x_it+=3
                STEcnt+=3
            j=(i-3*int(j))/2
            for k in range (int(j)):
                int_sum+=one_by_three_rule(x[x_it+0],x[x_it+1],x[x_it+2],fx[x_it+0],fx[x_it+1],fx[x_it+2])
                plt.fill_between(x[x_it+0:x_it+3], fx[x_it+0:x_it+3], color='red')
                x_it+=2
                SOTcnt+=2
        elif(i==1):
            #print(TRcnt)
            int_sum+=trapizoid_rule(x[x_it+0],x[x_it+1],fx[x_it+0],fx[x_it+1])
            plt.fill_between(x[x_it+0:x_it+2], fx[x_it+0:x_it+2], color='yellow')
            x_it+=1
            TRcnt+=1
        else:
            int_sum+=three_by_eight_rule(x[x_it+0],x[x_it+1],x[x_it+2],x[x_it+3],fx[x_it+0],fx[x_it+1],fx[x_it+2],fx[x_it+3])
            plt.fill_between(x[x_it+0:x_it+4], fx[x_it+0:x_it+4], color='blue')
            x_it+=3
            STEcnt+=3
            i2=i-3
            j=(i2-2)/3
            #print(j)
            for k in range (int(j)):
                int_sum+=three_by_eight_rule(x[x_it+0],x[x_it+1],x[x_it+2],x[x_it+3],fx[x_it+0],fx[x_it+1],fx[x_it+2],fx[x_it+3])
                plt.fill_between(x[x_it+0:x_it+4], fx[x_it+0:x_it+4], color='blue')
                x_it+=3
                STEcnt+=3
            j=(i2-3*int(j))/2
            #print(j)
            for k in range (int(j)):
                int_sum+=one_by_three_rule(x[x_it+0],x[x_it+1],x[x_it+2],fx[x_it+0],fx[x_it+1],fx[x_it+2])
                plt.fill_between(x[x_it+0:x_it+3], fx[x_it+0:x_it+3], color='red')
                x_it+=2
                SOTcnt+=2
    return(int_sum,SOTcnt,STEcnt,TRcnt)
    

def numerical_integrator(n,x,fx):
    sivlen=[]
    SameIntervalCounter(n,x,sivlen)
    return Integration(n,x,fx,sivlen)
    
def Plot(x,fx):
    plt.figure(figsize=(10,10))
    plt.grid()
    plt.scatter(x,fx, s=100)
    plt.plot(x,fx, color='black')
    plt.title('Numerical Integration')
    plt.xlabel('x values')
    plt.ylabel('y values')
    red_patch = mpatches.Patch(color='red', label='Simpsons 1/3 rule')
    blue_patch = mpatches.Patch(color='blue', label='Simpsons 3/8 rule')
    yellow_patch = mpatches.Patch(color='yellow', label='Trapizoid rule')
    plt.legend(loc='upper left', title='Intigration Rules', handles=[red_patch, blue_patch, yellow_patch])
    
    

x=[]
fx=[]

file1 = open("input8.txt","r+")  
  

n=int(file1.readline())

for i in range(n):  
    t=file1.readline()
    l=t.split(' ')         
    x.append(float(l[0]))
    fx.append(float(l[1]))

file1.close()
#print(fx)
Plot(x,fx)

ans=numerical_integrator(n,x,fx)
print('Trapezoid:',ans[3],'intervals\n1/3 rule:', ans[1],'intervals\n3/8 rule:', ans[2],'intervals')
print('Integral value:', ans[0])


#issues:sort, graph(curve?)