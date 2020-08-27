# -*- coding: utf-8 -*-
"""
Created on Sun Jul 21 23:20:39 2019

@author: Rasman Swargo
"""
import numpy as np
import matplotlib.pyplot as plt

def xpowgenerator(xpow, n, xpowsum):
    for i in range (6):
        sum=0
        for j in range (n):
            xpow[i][j]=xpow[0][j]**(i+1)
            sum+=xpow[i][j]
        xpowsum.append(sum)
    #print(xpowsum)
            
def xpowygenerator(xpowy, xpow, y, n, xpowysum):
    for i in range (6):
        sum=0
        for j in range (n):
            xpowy[i][j]=xpow[i][j]*y[j]
            sum+=xpowy[i][j]
        xpowysum.append(sum)
   #print(xpowysum)
    
def matrixgenerator(A,B,xpowysum, xpowsum, n, degree):
    A1=[]
    A1.append(n)
    for i in range (degree):
        A1.append(xpowsum[i])
    A.append(A1)
    for i in range (degree):
        A1=[]
        for j in range(degree+1):
            A1.append(xpowsum[i+j])
        A.append(A1)
    #print(A)
    sum=0
    for i in range (n):
        sum+=y[i]
    B.append(sum)
    for i in range (degree):
        B.append(xpowysum[i])
    #print(B)
def stcalculator(y, n):
    avg=0
    for i in range(n):
        avg+=y[i]
    avg=avg/n
    sum=0
    for i in range(n):
        sum+=((y[i]-avg)**2)
    return sum

def srcalculator(y, n, xpow, solve, degree):
    sum=0
    for i in range(n):
        ybf=0
        for j in range (degree+1):
            ybf+=solve[j]*(xpow[0][i]**j)
        sum+=((y[i]-ybf)**2)
    return sum
        
xpow=[]
xpowy=[]
xpowsum=[]
xpowysum=[]
y=[]
A=[]
B=[]

file1 = open("data.txt","r")    
linecnt=0
for line in file1:
    linecnt+=1
    y.append(0)
file1.seek(0)

for i in range(6):  
    k =[] 
    o=[]
    for j in range(linecnt):       
         k.append(0)
         o.append(0)
    xpow.append(k)
    xpowy.append(o)
    
for i in range (linecnt):
    k=file1.readline()
    l=k.split(' ')
    xpow[0][i]=float(l[0])
    y[i]=float(l[1])

file1.close()

plt.figure(figsize=(15,15))
plt.scatter(xpow[0],y)
plt.title('Linear & Multiple Regression')
plt.xlabel('x')
plt.ylabel('y')


xpowgenerator(xpow, linecnt, xpowsum)
xpowygenerator(xpowy, xpow, y, linecnt, xpowysum)
X=np.arange(0,20,0.01)


matrixgenerator(A,B,xpowysum, xpowsum, linecnt, 1)
solve1=np.linalg.solve(A,B)
Y1=solve1[0]+solve1[1]*X
plt.plot(X, Y1, color='blue', linewidth=3, label='First Order')
sr1=srcalculator(y, linecnt, xpow, solve1, 1)
#print(sr1)
st1=stcalculator(y, linecnt)
r1=(1-(sr1/st1))**(0.5)
print("First Order Equation\ny=",solve1[0],"+(",solve1[1],")* x")
print("st= ",st1,"\nsr= ", sr1,"\nr= ", r1)

A=[]
B=[]
matrixgenerator(A,B,xpowysum, xpowsum, linecnt, 2)
solve2=np.linalg.solve(A,B)
Y2=solve2[0]+solve2[1]*X+solve2[2]*X*X
plt.plot(X, Y2,color='violet', linewidth=3, label='Second Order')
sr2=srcalculator(y, linecnt, xpow, solve2, 2)
r2=(1-(sr2/st1))**(0.5)
#print(sr2)
print("Second Order Equation\ny=",solve2[0],"+(",solve2[1],")* x +(",solve2[2],")* x^2")
print("st= ",st1,"\nsr= ", sr2,"\nr= ", r2)

A=[]
B=[]
matrixgenerator(A,B,xpowysum, xpowsum, linecnt, 3)
solve3=np.linalg.solve(A,B)
Y3=solve3[0]+solve3[1]*X+solve3[2]*X*X+solve3[3]*X*X*X
plt.plot(X, Y3, color='green', linewidth=3, label='Third Order')
plt.legend(loc='upper left')
sr3=srcalculator(y, linecnt, xpow, solve3, 3)
r3=(1-(sr3/st1))**(0.5)
#print(sr2)
print("Third Order Equation\ny=",solve3[0],"+(",solve3[1],")* x +(",solve3[2],")* x^2+(",solve3[3],")* x^3")
print("st= ",st1,"\nsr= ", sr3,"\nr= ", r3)