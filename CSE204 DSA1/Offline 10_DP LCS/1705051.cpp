#include<bits/stdc++.h>

using namespace std;

class LCS
{
    string x,y;
    int x_len,y_len;
    int **c; //for lcs table formulation
    int **b; //for direction Up=1, Left=-1, Diagonal=0


public:
    LCS();
    void LCSTable();
    void PrintLCS(int i, int j);
    ~LCS();
};

LCS::LCS()
{
    cout<<"Give the first String: ";
    cin>>x;
    cout<<"Give the second String: ";
    cin>>y;
    x_len=x.length();
    y_len=y.length();
    x_len++;
    y_len++;
    c = new int*[x_len];
    for(int i=0; i<x_len; i++) c[i]=new int[y_len];
    b = new int*[x_len];
    for(int i=0; i<x_len; i++) b[i]=new int[y_len];
    //cout<<"Par hoise"<<endl;
}

void LCS::LCSTable()
{
    for(int i=0; i<x_len; i++) c[i][0]=0;
    for(int i=0; i<y_len; i++) c[0][i]=0;
    //cout<<"Par hoise2"<<endl;
    //cout<<x_len<<y_len;
    for(int i=1; i<x_len; i++)
    {
        for(int j=1; j<y_len; j++)
        {
            if(x[i-1]==y[j-1])
            {
                //cout<<i-1<<','<<j-1<<','<<x[i-1]<<endl;
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=0;
            }

            else
            {
                if(c[i-1][j]>c[i][j-1])
                {
                    c[i][j]=c[i-1][j];
                    b[i][j]=1;
                }

                else
                {
                    c[i][j]=c[i][j-1];
                    b[i][j]=-1;
                }

            }
        }
    }
    //cout<<"Par hoise3"<<endl;
    //cout<<c[x_len-1][y_len-1]<<endl;
    this->PrintLCS(x_len-1,y_len-1);
    //cout<<"Par hoise4"<<endl;
    /*for(int i=0; i<x_len; i++)
    {
        for(int j=0; j<y_len; j++)
        {
            cout<<c[i][j]<<' ';
        }
        cout<<endl;
    }

    for(int i=1; i<x_len; i++)
    {
        for(int j=1; j<y_len; j++)
        {
            cout<<b[i][j]<<' ';
        }
        cout<<endl;
    }*/
}

void LCS::PrintLCS(int i, int j)
{
    //cout<<"Par hoise5"<<endl;
    if(i==0 || j==0) return;
    if(b[i][j]==0)
    {
        //cout<<i<<','<<j<<endl;
        PrintLCS(i-1,j-1);
        cout<<x[i-1];
    }
    else if(b[i][j]==1) PrintLCS(i-1,j);
    else PrintLCS(i,j-1);
}

LCS::~LCS()
{
    delete c;
    delete b;
}

int main()
{
    LCS new_lcs;
    new_lcs.LCSTable();
    return 0;
}

