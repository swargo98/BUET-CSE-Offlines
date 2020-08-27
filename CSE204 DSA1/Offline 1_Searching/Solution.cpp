#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include <iomanip>
#include<chrono>

using namespace std;

int linear_search(int a[], int a_size, int element)
{
    for(int k=0; k<a_size; k++)
        if(a[k]==element) return k;

    return -1;
}

int bin_search(int a[], int a_size, int element)
{
    int l=0, h=a_size-1, mid;
    while(h>=l)
    {
        mid=(l+h)/2;
        if(a[mid]==element)
            return mid;

        else if(a[mid]>element)
            h=mid-1;

        else
            l=mid+1;
    }

    return -1;
}

int main()
{
    srand(time(0));
    int array_sizes[] = {10,100,200,500,1000,2000,5000,10000, 100000};
    int* p;
    double lin_t_sum=0, bin_t_sum=0;
    int lin_ind, bin_ind;
    for(int i=0; i<9; i++)
    {
        lin_t_sum=0;
        bin_t_sum=0;
        int cur_array_size = array_sizes[i];
        cout<<"For n= "<<cur_array_size<<endl<<endl;
        p= new int [cur_array_size];
        for(int j=0; j<cur_array_size; j++) p[j]= rand()%cur_array_size;
        sort(p, p+cur_array_size);

        for(int x=0; x<100000; x++)
        {
            int element = rand() % (cur_array_size+10);

        auto start = chrono::high_resolution_clock::now();

        lin_ind=linear_search(p, cur_array_size, element);

        auto end = chrono::high_resolution_clock::now();

        double time_taken_lin = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        //cout<<"Lin: "<<time_taken_lin<<endl;

       lin_t_sum+=time_taken_lin/1000;

        auto start_binary = chrono::high_resolution_clock::now();

        bin_ind=bin_search(p, cur_array_size, element);

        auto end_binary = chrono::high_resolution_clock::now();

        double time_taken_bin = chrono::duration_cast<chrono::nanoseconds>(end_binary - start_binary).count();

        //cout<<"Bin: "<<time_taken_bin<<endl;

        bin_t_sum+=time_taken_bin/1000;


        }

        //cout<<lin_t_sum<<' '<<bin_t_sum<<endl;

        cout << "Average Time taken by linear search is : " << fixed << lin_t_sum/(100000);
        cout << " microsec" << endl<< endl;

         cout << "Average Time taken by binary search is : " << fixed << bin_t_sum/(100000); //<< setprecision(9);
        cout << " microsec" << endl<< endl;

    }

    return 0;
}

