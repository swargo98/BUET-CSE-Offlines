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

void gen_avg(int a[], int n)
{
    srand(time(0));
    for(int i=0; i<n; i++) a[i]=rand()%1000;
}

void gen_best(int a[], int n)
{
    srand(time(0));
    a[0]=rand()%1000;
    for(int i=1; i<n; i++) a[i]=a[i-1]+rand()%1000;
}


void gen_worst(int a[], int n)
{
    srand(time(0));
    a[n-1]=rand()%1000;
    for(int i=(n-2); i>-1; i--) a[i]=a[i+1]+rand()%1000;
}


int main()
{
    int choice, n;
    int* ar;
    LARGE_INTEGER frequency;
    LARGE_INTEGER t1, t2;
    double elapsedTime;
    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            scanf("%d", &n);
            ar=0;
            ar=new int[n];
            gen_avg(ar,n);
            break;

        case 2:
            printf("Number of elements: ");
            scanf("%d", &n);
            ar=0;
            ar=new int[n];
            gen_best(ar,n);
            break;

        case 3:
            printf("Number of elements: ");
            scanf("%d", &n);
            ar=0;
            ar=new int[n];
            gen_worst(ar,n);
            break;

        case 4:
            printf("Applying merge sort\n");
            // do yourself
            //mergesort(ar,0,n-1);
            // this should transform the given array into a sorted array
            LARGE_INTEGER frequency;
            LARGE_INTEGER t1, t2;
            double elapsedTime;

            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&t1);
            mergesort(ar,0,n-1);
            QueryPerformanceCounter(&t2);
            elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

            cout<<"Time taken to finish: "<<elapsedTime<<"ms\n";
            break;

        case 5:
            printf("Applying quicksort\n");
            // do yourself
            //quicksort(ar,0, n-1);
            // this should transform the given array into a sorted array


            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&t1);
            quicksort(ar,0,n-1);
            QueryPerformanceCounter(&t2);
            elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

            cout<<"Time taken to finish: "<<elapsedTime<<"ms\n";
            break;

        case 6:
            printf("Array\n");
            printarray(ar,n);
            break;
        }
    }
}

