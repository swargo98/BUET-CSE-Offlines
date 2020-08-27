import numpy as np
import matplotlib.pyplot as plot

def fn(x):
    fx=((x/(1-x))*(6/(2+x))**0.5)-0.05
    return fx
    
def Secant(fgs, sgs, erar, mi):
    it=0
    rar=1
    while(erar<=rar):
        it=it+1
        tgs=sgs
        sgs=fgs
        fgs=sgs-fn(sgs)*((tgs-sgs)/(fn(tgs)-fn(sgs)))
        rar=np.abs(fgs-sgs)/fgs
        if(it>mi):
            return [-1,-1]
    return [fgs, it]

def fposition(lb, ub, erar, mi):
    '''il=0
    iu=0'''
    it=0
    xr=lb
    xrold=ub
    rar=1
    fu=fn(ub)
    fl=fn(lb)
        
    while(erar<=rar):
        it=it+1
        xrold=xr
        xr=ub-fu*(lb-ub)/(fl-fu)
        fr=fn(xr)
        rar=np.abs(xr-xrold)/xr
        test=fl*fr
        if test<0 :
            ub=xr
            fu=fn(ub)
            '''iu=0
            il=il+1
            if il>1 :
                fl=fl/2'''
        elif test>0 :
            lb=xr
            fl=fn(lb)
            '''il=0
            iu=iu+1
            if iu>1 :
                fu=fu/2'''
        
        else :
            return [xr, it]
            
        if it>mi :
            return [-1,-1]
        
    return [xr, it]
        
    
        

x=np.arange(0,1,0.001)
e=fn(x)
fgs=input('Lower Bound: ')
fgs=float(fgs)
sgs=input('Upper Bound: ')
sgs=float(sgs)
maxit=input('Max Iteration: ')
maxit=int(maxit)
erar=0.005
fig= plot.figure(figsize=(10,10))
plot.figure(1)
plot.grid()
plot.plot(x,e, color='red', linewidth=5)

idx = np.argwhere(np.diff(np.sign(e - 0))).flatten()
print('Estimation from graph: ', x[idx])

print('Secant Method Result and Iteration Number: ', Secant(fgs, sgs, erar, maxit))
print('False Position Method Result and Iteration Number: ', fposition(fgs, sgs, erar, maxit))

