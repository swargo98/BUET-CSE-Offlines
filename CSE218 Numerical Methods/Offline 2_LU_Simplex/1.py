import numpy as np
import math
import sys

def truncate(number, digits) -> float:
    stepper = 10.0 ** digits
    return math.trunc(stepper * number) / stepper


def decompose (a,n,L,U):
    for k in range(0, n-1, 1):
        for i in range(k+1, n, 1):
            if(a[k][k]==0):
                factor=np.inf
                #continue
            elif(a[k][k]==np.inf):
                factor=0
            else:
                factor=a[i][k]/a[k][k]
            #print(i,k,factor)
            a[i][k]=factor
            for j in range(k+1, n, 1):
                a[i][j]=a[i][j]-factor*a[k][j]
                
def Lgenerator(a,n,L):
    for c in range(0, n-1, 1):
        for r in range(c+1,n,1):
            L[r][c]=a[r][c]

def Ugenerator(a,n,U):
    for r in range(0,n,1):
        for c in range(r,n,1):
            U[r][c]=a[r][c]
            
def HasUniqueSol(U,n):
    for r in range(0,n,1):
        cnt=0
        for c in range(0,n,1):
            if(U[r][c]==0):
                 cnt=cnt+1
        if(cnt==n):
            return False
            

def forward_substitute(a,n,b):
    for i in range(1, n, 1):
        sum=b[i]
        for j in range(0, i, 1):
            sum=sum-a[i][j]*b[j]
        b[i]=sum

def Ygenerator(Y,b,n):
    for i in range(0,n,1):
        Y[i]=b[i]


def backward_substitution(a,n,b,x):
    x[n-1]=b[n-1]/a[n-1][n-1]
    for i in range(n-2, -1, -1):
        sum=0
        for j in range(i+1, n, 1):
            sum=sum+a[i][j]*x[j]
        x[i]=(b[i]-sum)/a[i][i]
        



a=[]
L=[]
U=[]
b=[]
Y=[]
x=[]

file1 = open("in1.txt","r+")  
  

n=int(file1.readline())

for i in range(n):  
    t=file1.readline()
    l=t.split(' ')         
    k =[] 
    m=[]
    o=[]
    for j in range(n):       
         k.append(float(l[j]))
         o.append(0)
         if(i==j):
             m.append(1)
         else:
             m.append(0)
    a.append(k)
    L.append(m)
    U.append(o)
    Y.append(0)
    x.append(0)

for k in range(0,n,1):
    t=file1.readline()
    b.append(int(t)) 
file1.close() 
#Lgenerator(a,n,L)

#c=3
#print(truncate(c,2))
#a[0][0]=0.3456
#print('%.2f' % a[0][0])
#g='%.2f' % .3456
#print(g)
#print(a)
#print(L)
#print(U)
#print(Y)
#print(x)

fout=open("out1.txt", "w")

decompose(a,n,L,U)
Lgenerator(a,n,L)
Ugenerator(a,n,U)

for i in range (n):
    for j in range (n):
        g= '%.4f' % L[i][j]
        fout.write(str(g)+' ')
    fout.write("\n")

fout.write("\n")

for i in range (n):
    for j in range (n):
        g= '%.4f' % U[i][j]
        fout.write(str(g)+' ')
    fout.write("\n")
        
fout.write("\n")

if(HasUniqueSol(U,n)==False):
    fout.write('Unique Solution Not Achievable'+'\n')
    fout.close()
    sys.exit()
    
forward_substitute(a,n,b)
Ygenerator(Y,b,n)
backward_substitution(a,n,b,x)

for j in range (n):
    g= '%.4f' % Y[j]
    fout.write(str(g)+'\n')

fout.write("\n")
    
for j in range (n):
    g= '%.4f' % x[j]
    fout.write(str(g)+'\n')
fout.close()    
#3 3 -0.1 -0.2 0.1 7 -0.3 0.3 -0.2 10 7.85 -19.3 71.4