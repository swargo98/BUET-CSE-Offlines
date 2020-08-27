import numpy as np
import matplotlib.pyplot as plt

def HighestNegative(a, m, n):
    x=999999
    for i in range (m+n+1):
        if(a[0][i]<0 and a[0][i]<x):
            x=a[0][i]
            ind=i
    if(x==999999):
        return -1
    else:
        return ind
        
def intercept(a,col,m,n):
    for i in range(1,(m+1),1):
        if(a[i][col]==0):
            a[i][m+n+2]=np.inf
        elif(a[i][col]==np.inf):
            a[i][m+n+2]=0
        else:
            a[i][m+n+2]=a[i][m+n+1]/a[i][col]

def LowestIntercept(a,m,n):
    x=999999999
    for i in range (1,(m+1),1):
        if(a[i][m+n+2]>0 and a[i][m+n+2]<x):
            x=a[i][m+n+2]
            ind=i
    if(x==999999999):
        return -1
    else:
        return ind
def pivoting(a,m,n,row,col, rowname, colname):
    d=a[row][col]
    rowname[row+1]=colname[col]
    for i in range (m+n+2):
        if(d==0):
            a[row][i]=np.inf
        elif(d==np.inf):
            a[row][i]=0
        a[row][i]=a[row][i]/d

def gauss_jordan(a,m,n,row,col):
    for i in range (m+1):
        if(i!=row):
            if(a[i][col]!=0):
                d=a[i][col]
                for j in range (m+n+2):
                    a[i][j]=a[i][j]-d*a[row][j]
                    
def PrintTable(a,m,n, rowname, colname):
    for i in range (m+2):
        print(rowname[i], end='\t')
        for j in range (m+n+3):
            if(i==0):
                print(colname[j], end='\t')
            else:
                print('%.2f' % a[i-1][j], end='\t')
        print()
        
def PrintResult(a,m,n,rowname, colname):
    print('Result: ')
    print('Z= ', '%.2f' % a[0][m+n+1])
    for i in range (n):
        s='x'+str(i+1)
        done=0
        for j in range (m+2):
            if(rowname[j]==s):
                print(s,'= ', '%.2f' % a[j-1][m+n+1])
                done=1
        if(done==0):
            print(s,'= 0')
            
    

def simplex_method(a,m,n,rowname, colname):
    print('Original Table: ')
    PrintTable(a,m,n, rowname, colname)
    it=0
    while(HighestNegative(a,m,n)!=-1):
        it=it+1
        col=HighestNegative(a,m,n)
        intercept(a,col,m,n)
        #print('After Intercept: ')
        #PrintTable(a,m,n, rowname, colname)
        row=LowestIntercept(a,m,n)
        pivoting(a,m,n,row,col, rowname, colname)
        #print('After Pivoting: ')
        #PrintTable(a,m,n, rowname, colname)
        gauss_jordan(a,m,n,row,col)
        print('After', it,'th Iteration: ')
        PrintTable(a,m,n, rowname, colname)
    PrintResult(a,m,n,rowname, colname)


a=[]
file1 = open("in2.txt","r+")    
mcnt=0
ncnt=0
for line in file1:
    mcnt+=1
mcnt=mcnt-1
file1.seek(0)

x=[]
x.append(1)
k=file1.readline()
l=k.split(' ')
for i in l:
    ncnt+=1
    #print(i)
    x.append(float(i)*-1)
for i in range(mcnt+2):
    x.append(0)
a.append(x)
#print(x)   

colname=[]
rowname=[]
rowname.append('Basic')
rowname.append('Z')
colname.append('Z')
for i in range (ncnt):
    s='x'+str(i+1)
    colname.append(s)

for i in range (mcnt):
    s='s'+str(i+1)
    rowname.append(s)
    colname.append(s)
colname.append('Res')
colname.append('Intc')
#print(rowname)
#print(colname)

for i in range (mcnt):
    x=[]
    x.append(0)
    k=file1.readline()
    l=k.split(' ')
    for j in range (ncnt):
        x.append(float(l[j]))
    for j in range (mcnt):
        if(i==j):
            x.append(1)
        else:
            x.append(0)
    x.append(float(l[ncnt]))
    x.append(0)
    a.append(x)
    #print(x)


file1.close() 
#PrintTable(a, mcnt, ncnt, rowname, colname)
if(ncnt==2):
    x = np.linspace(0, 50, 5000)
    y=[]
    for i in range(mcnt):
        y.append(x)
    for i in range(mcnt):
        #print(a[i+1][mcnt+ncnt+1])
        if(a[i+1][2]==0):
            xtemp=x*0+(a[i+1][mcnt+ncnt+1])/(a[i+1][1])
            #print(xtemp)
            plt.plot(xtemp,x)
            y[i]=x*(9999)
            continue                                          
        y[i]=((a[i+1][mcnt+ncnt+1])-x*(a[i+1][1]))/(a[i+1][2])
            
        
    for i in range(mcnt):
        #print(y[i])
        plt.plot(x, y[i])
    
plt.xlim((0, 30))
plt.ylim((0, 30))

ymin = y[0]
for i in range(mcnt):
    ymin = np.minimum(ymin, y[i])
    #print(ymin)

y6=0
plt.fill_between(x, ymin, y6, where=ymin>y6, color='grey', alpha=0.5)


simplex_method(a, mcnt, ncnt, rowname, colname)