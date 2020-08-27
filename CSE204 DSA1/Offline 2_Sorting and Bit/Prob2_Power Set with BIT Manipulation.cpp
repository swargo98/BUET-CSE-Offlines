#include <bits/stdc++.h>
#include<windows.h>

using namespace std;

unordered_set<string> power_set;

void powerSet(string str, int str_size)
{
    string subset;
	int n=pow(2,str_size);
	for(int i=0; i<n; i++)
    {
        subset.clear();
        for(int j=0; j<str_size; j++)
        {
            if(i & (1<<j)) subset+=str[j];
        }
        //cout<<"Vitre "<<subset<<endl;
        power_set.insert(subset);
    }
}

int main()
{
    srand(time(0));
    LARGE_INTEGER frequency;
    LARGE_INTEGER t1, t2;
    double elapsedTime;
    int str_size;
    cin>>str_size;
	string str="";
	for(int i=0; i<str_size; i++)
    {
        int r=rand()%62;
        char c;
        if(r<26) c='a'+r;
        else if(r<52) c='A'+(r-26);
        else c='0'+(r-52);
        str+=c;
    }
    //string str="111";
    sort(str.begin(), str.end());
    cout<<str<<endl;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t1);
	powerSet(str, str_size);
	QueryPerformanceCounter(&t2);
    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

    cout<<"Subsets of the power set:"<<endl;

    //for(string s: power_set) cout<<s<<endl;

    cout << elapsedTime << " ms.\n";

	return 0;
}
