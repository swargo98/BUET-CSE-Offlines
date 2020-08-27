#include <cstdio>
#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>

using namespace std;

void printarray(int ar[], int size)
{
    for(int i=0; i<size; i++) cout<<ar[i]<<' ';
    cout<<endl;
}

void merge(int ar[], int low, int mid, int high)
{
    int n1=mid-low+1;
    int n2=high-mid;
    int ar1[n1+1];
    int ar2[n2+1];
    for(int i=0; i<n1; i++) ar1[i]=ar[low+i];
    for(int i=0; i<n2; i++) ar2[i]=ar[mid+1+i];
    ar1[n1]=INFINITY;
    ar2[n2]=INFINITY;
    int i=0;
    int j=0;
    for(int k=low; k<=high; k++)
    {
        if(ar1[i]<=ar2[j])
        {
            ar[k]=ar1[i++];
        }
        else ar[k]=ar2[j++];
    }
}

void mergesort(int ar[], int low, int high)
{
    if(low<high)
    {
        int mid=(high+low)/2;
        mergesort(ar, low, mid);
        mergesort(ar, mid+1, high);
        merge(ar, low, mid, high);
    }
}

void Swap(int& a, int& b)
{
    int t=a;
    a=b;
    b=t;
}

int Partition(int a[], int low, int high)
{
    int x=a[high];
    int i = low-1;
    for(int j=low; j<high; j++) if(a[j]<=x) Swap(a[++i], a[j]);
    Swap(a[++i], a[high]);
    return i;
}

void quicksort(int ar[], int low, int high)
{
    if(low<high)
    {
        int pivot=Partition(ar,low,high);
        quicksort(ar, low, pivot-1);
        quicksort(ar, pivot+1, high);
    }
}

int main()
{
    int choice, n;
    int* ar;
    int* ar2;
    LARGE_INTEGER frequency;
    LARGE_INTEGER t1, t2;
    double elapsedTime;
    while(1)
    {
        printf("1. Generate average case stat\n");
        printf("2. Generate best case stat\n");
        printf("3. Generate worst case stat\n");

        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            for(int i=10; i<=10000; i*=10)
            {
                LARGE_INTEGER frequency;
                LARGE_INTEGER t1, t2;
                double elapsedTime_merge=0;
                double elapsedTime_quick=0;
                srand(time(0));
                for(int j=0; j<100; j++)
                {
                    ar=0;
                    ar2=0;
                    ar=new int[i];
                    ar2=new int[i];

                    for(int X=0; X<i; X++)
                    {
                        ar[X]=rand()%1000;
                        ar2[X]=ar[X];
                    }

                    //printarray(ar,i);
                    //printarray(ar2,i);
                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&t1);
                    mergesort(ar,0,i-1);
                    QueryPerformanceCounter(&t2);
                    elapsedTime_merge += (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

                    //printarray(ar,i);
                    //printarray(ar2,i);

                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&t1);
                    quicksort(ar2,0,i-1);
                    QueryPerformanceCounter(&t2);
                    elapsedTime_quick += (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

                    //printarray(ar,i);
                    //printarray(ar2,i);

                }
                cout<<"Avg Time taken to finish mergesort for n= "<<i<<" : "<<elapsedTime_merge/100<<" ms\n";
                cout<<"Avg Time taken to finish quicksort for n= "<<i<<" : "<<elapsedTime_quick/100<<" ms\n";
                cout<<endl;
            }
            break;

        case 2:
            for(int i=10; i<=10000; i*=10)
            {
                LARGE_INTEGER frequency;
                LARGE_INTEGER t1, t2;
                double elapsedTime_merge=0;
                double elapsedTime_quick=0;
                srand(time(0));

                for(int j=0; j<100; j++)
                {
                    ar=0;
                    ar2=0;
                    ar=new int[i];
                    ar2=new int[i];
                    ar[0]=rand()%1000;
                    ar2[0]=ar[0];
                    //cout<<"jhvj"<<endl;
                    for(int X=1; X<i; X++)
                    {
                        ar[X]=ar[X-1]+rand()%1000;
                        ar2[X]=ar[X];
                    }

                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&t1);
                    mergesort(ar,0,i-1);
                    QueryPerformanceCounter(&t2);
                    elapsedTime_merge += (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&t1);
                    quicksort(ar2,0,i-1);
                    QueryPerformanceCounter(&t2);
                    elapsedTime_quick += (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
                }
                cout<<"Time taken to finish mergesort(sorted) for  n= "<<i<<" : "<<elapsedTime_merge/100<<" ms\n";
                cout<<"Time taken to finish quicksort(sorted) for  n= "<<i<<" : "<<elapsedTime_quick/100<<" ms\n";
                cout<<endl;
            }
            break;
        case 3:
            for(int i=10; i<=10000; i*=10)
            {
                //if(i==10000) i=5000;
                LARGE_INTEGER frequency;
                LARGE_INTEGER t1, t2;
                double elapsedTime_merge=0;
                double elapsedTime_quick=0;
                srand(time(0));

                for(int j=0; j<100; j++)
                {
                    ar=0;
                    ar2=0;
                    ar=new int[i];
                    ar2=new int[i];

                    ar[i-1]=rand()%1000;
                    ar2[0]=ar[0];
                    for(int X=(i-2); X>-1; X--)
                    {
                        ar[X]=ar[X+1]+rand()%1000;
                        ar2[X]=ar[X];
                    }

                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&t1);
                    mergesort(ar,0,i-1);
                    QueryPerformanceCounter(&t2);
                    elapsedTime_merge += (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&t1);
                    quicksort(ar2,0,i-1);
                    QueryPerformanceCounter(&t2);
                    elapsedTime_quick += (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
                }
                cout<<"Time taken to finish mergesort(reversely sorted) for n= "<<i<<" : "<<elapsedTime_merge/100<<" ms\n";
                cout<<"Time taken to finish quicksort(reversely sorted) for n= "<<i<<" : "<<elapsedTime_quick/100<<" ms\n";
                cout<<endl;
            }
            break;

        }
    }
}


