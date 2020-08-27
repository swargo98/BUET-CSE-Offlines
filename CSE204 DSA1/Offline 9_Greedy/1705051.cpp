#include<bits/stdc++.h>


using namespace std;

int SelectionSortGreedy(int s[], int f[],  int ind[], int n)
{
    for(int i=0; i<(n-1); i++)
    {
        int min_ind=i;
        for(int j=i+1; j<n; j++)
        {
            if(f[j]<f[min_ind])
            {
                min_ind=j;

            }
        }
        int k = f[min_ind];
        f[min_ind]=f[i];
        f[i]=k;

        k = s[min_ind];
        s[min_ind]=s[i];
        s[i]=k;

        k = ind[min_ind];
        ind[min_ind]=ind[i];
        ind[i]=k;


    }
}


class ActivitySelection
{
    int *start;
    int *finish;
    int *ind;
    int NOfAct;
public:
    ActivitySelection();
    void Print_Activities();
    void Select_Activities();
    ~ActivitySelection();
};

ActivitySelection::ActivitySelection()
{
    cout<<"Give number of intervals: ";
    cin>>NOfAct;
    start=new int[NOfAct];
    finish=new int[NOfAct];
    ind=new int[NOfAct];
    finish[0]=rand()%NOfAct;
    start[0]=rand()%finish[0];
    ind[0]=0;
    for(int i=1; i<NOfAct; i++)
    {
        finish[i]=(rand()%NOfAct);
        //finish[i]=finish[i-1]+(rand()%NOfAct);
        start[i]=finish[i]-(rand()%finish[i]);
        if(start[i]==finish[i]) finish[i]++;
        //cout<<start[i]<<endl;
        ind[i]=i;
    }

}

void ActivitySelection::Print_Activities()
{
    for(int i=0; i<NOfAct; i++)
    {

        cout<<"Item "<<ind[i]+1<<": {"<<start[i]<<", "<<finish[i]<<"}"<<endl;
    }
    cout<<endl;
}

void ActivitySelection::Select_Activities()
{
    SelectionSortGreedy( start,  finish,  ind, NOfAct);
    int SelectedInd=0;

    cout<<"Selected Actions:"<<endl;
    cout<<"Item "<<ind[0]+1<<": {"<<start[0]<<", "<<finish[0]<<"}"<<endl;

    for(int i=1; i<NOfAct; i++)
    {
        if(start[i]>finish[SelectedInd])
        {
            cout<<"Item "<<ind[i]+1<<": {"<<start[i]<<", "<<finish[i]<<"}"<<endl;
            SelectedInd=i;
        }
    }
    cout<<endl;
}

ActivitySelection::~ActivitySelection()
{
    delete start;
    delete finish;
}

int main()
{
    ActivitySelection NewActivity;
    NewActivity.Print_Activities();
    NewActivity.Select_Activities();
    return 0;
}
