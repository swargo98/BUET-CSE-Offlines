#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include <iomanip>
#include<chrono>

using namespace std;

int SelectionSort(int a[], int n)
{
    for(int i=0; i<(n-1); i++)
    {
        int min_ind=i;
        for(int j=i+1; j<n; j++)
        {
            if(a[j]<a[min_ind])
            {
                min_ind=j;

            }
        }
        int k = a[min_ind];
        a[min_ind]=a[i];
        a[i]=k;
    }
}

int InsertionSort(int a[], int n)
{
    for(int i=1; i<n; i++)
    {
        int j=i-1;
        int t=a[i];
        while(j>=0 && t<a[j])
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=t;
    }
}

int main()
{
    srand(time(0));
    int array_sizes[] = {10,100,200,500,1000,2000,5000,10000, 100000};
    int* p,*q;
    double s_sort_t_sum=0, i_sort_t_sum=0, i_sort_t_sum_best=0, i_sort_t_sum_worst=0, s_sort_t_sum_best=0, s_sort_t_sum_worst=0;

    for(int i=0; i<8; i++)
    {
        //cout<<array_sizes[i]<<endl;
        s_sort_t_sum=0;
        i_sort_t_sum=0;
        i_sort_t_sum_best=0;
        i_sort_t_sum_worst=0;
        s_sort_t_sum_best=0;
        s_sort_t_sum_worst=0;
        int cur_array_size = array_sizes[i];
        cout<<"For n= "<<cur_array_size<<endl<<endl;
        p= new int [cur_array_size];
        q= new int [cur_array_size];


        for(int x=0; x<1000; x++)
        {

            for(int j=0; j<cur_array_size; j++)
            {
                p[j]= rand()%cur_array_size;
                q[j]=p[j];
            }

            auto start = chrono::high_resolution_clock::now();

            SelectionSort(p, cur_array_size);

            auto end = chrono::high_resolution_clock::now();

            double time_taken_s_sort = chrono::duration_cast<chrono::nanoseconds>(end - start).count();


            s_sort_t_sum+=time_taken_s_sort/1000;


            auto start_sel_sort_best = chrono::high_resolution_clock::now();

            SelectionSort(p, cur_array_size);

            auto end_sel_sort_best = chrono::high_resolution_clock::now();

            double time_taken_s_sort_best = chrono::duration_cast<chrono::nanoseconds>(end_sel_sort_best - start_sel_sort_best).count();

            s_sort_t_sum_best+=time_taken_s_sort_best/1000;

            reverse(p, p+cur_array_size);

            auto start_sel_sort_worst = chrono::high_resolution_clock::now();

            SelectionSort(p, cur_array_size);

            auto end_sel_sort_worst = chrono::high_resolution_clock::now();

            double time_taken_s_sort_worst = chrono::duration_cast<chrono::nanoseconds>(end_sel_sort_worst - start_sel_sort_worst).count();

            s_sort_t_sum_worst+=time_taken_s_sort_worst/1000;



            auto start_ins_sort = chrono::high_resolution_clock::now();

            InsertionSort(q, cur_array_size);

            auto end_ins_sort = chrono::high_resolution_clock::now();

            double time_taken_i_sort = chrono::duration_cast<chrono::nanoseconds>(end_ins_sort - start_ins_sort).count();

            i_sort_t_sum+=time_taken_i_sort/1000;


            auto start_ins_sort_best = chrono::high_resolution_clock::now();

            InsertionSort(q, cur_array_size);

            auto end_ins_sort_best = chrono::high_resolution_clock::now();

            double time_taken_i_sort_best = chrono::duration_cast<chrono::nanoseconds>(end_ins_sort_best - start_ins_sort_best).count();

            i_sort_t_sum_best+=time_taken_i_sort_best/1000;

            reverse(q, q+cur_array_size);

            auto start_ins_sort_worst = chrono::high_resolution_clock::now();

            InsertionSort(q, cur_array_size);

            auto end_ins_sort_worst = chrono::high_resolution_clock::now();

            double time_taken_i_sort_worst = chrono::duration_cast<chrono::nanoseconds>(end_ins_sort_worst - start_ins_sort_worst).count();

            i_sort_t_sum_worst+=time_taken_i_sort_worst/1000;



        }

        cout << "Best Case Time taken by Selection Sort is : " << fixed << s_sort_t_sum_best/(1000);
        cout << " microsec" << endl<< endl;

        cout << "Average Case Time taken by Selection Sort is : " << fixed << s_sort_t_sum/(1000);
        cout << " microsec" << endl<< endl;

        cout << "Worst Case Time taken by Selection Sort is : " << fixed << s_sort_t_sum_worst/(1000);
        cout << " microsec" << endl<< endl;

        cout << "Best Case Time taken by Insertion Sort is : " << fixed << i_sort_t_sum_best/(1000);
        cout << " microsec" << endl<< endl;

        cout << "Average Case Time taken by Insertion Sort is : " << fixed << i_sort_t_sum/(1000);
        cout << " microsec" << endl<< endl;

        cout << "Worst Case Time taken by Insertion Sort is : " << fixed << i_sort_t_sum_worst/(1000);
        cout << " microsec" << endl<< endl;

    }

    return 0;
}



