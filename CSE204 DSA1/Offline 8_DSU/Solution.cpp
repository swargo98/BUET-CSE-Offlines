#include<bits/stdc++.h>

using namespace std;
#define max 100

class DisjointSet
{
    int *Parent;
    int *RankParent;
    int n;

public:
    DisjointSet();
    DisjointSet(int highest_node);
    void Make_Set(int x);
    int Find_Set(int x);
    void Union(int u, int v);
    void Print(int u);
    ~DisjointSet();
};

DisjointSet::DisjointSet()
{
    Parent=new int[max];
    RankParent=new int[max];
    n=max;
    for(int i=0; i<max; i++)
    {
         Parent[i]=-1;
         RankParent[i]=-1;
    }
}

DisjointSet::DisjointSet(int highest_node)
{
    Parent=new int[highest_node];
    RankParent=new int[highest_node];
    n=highest_node;
    for(int i=0; i<highest_node; i++)
    {
         Parent[i]=-1;
         RankParent[i]=-1;
    }
}

void DisjointSet::Make_Set(int x)
{
    Parent[x]=x;
    RankParent[x]=0;
}

int DisjointSet::Find_Set(int x)
{
    if(Parent[x]==-1) return -1;
    if(x!=Parent[x])
        return Parent[x]=Find_Set(Parent[x]);
    return Parent[x];
}

void DisjointSet::Union(int u, int v)
{
    int PU=Find_Set(u);
    int PV=Find_Set(v);

    if(PU==PV) return;
    if(RankParent[PU]>RankParent[PV]) Parent[PV]= PU;
    else if(RankParent[PU]<RankParent[PV]) Parent[PU]= PV;
    else
    {
        Parent[PV]= PU;
        RankParent[PU]++;
    }
}

void DisjointSet::Print(int u)
{
    int p=Find_Set(u);
    if(u>max || p==-1)
    {
        cout<<"Invalid Input"<<endl;
        return;
    }

    for(int i=0; i<n; i++) if(Find_Set(i)==p) cout<<i<<' ';
    cout<<endl;
}

DisjointSet::~DisjointSet()
{
    delete Parent;
    delete RankParent;
}

int main()
{
    DisjointSet ds;
    int choice, n;
    while(1)
    {
        cout << "Give a choice : "<<endl;
        cout << "1. Make set(n) : " <<endl;
        cout << "2. Find(x) : "<<endl;
        cout << "3. Union(x,y) : " << endl;
        cout << "4. Print set(n) : "<<endl;
        cout << "5. Quit  " <<endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Give the element: "<<endl;
            cin >> n;
            ds.Make_Set(n);
        }
        else if (choice == 2)
        {
            cout << "Give the element you want to find : " <<endl;
            cin >> n;

            cout<<"Parent of the element is: "<<ds.Find_Set(n)<<endl;
        }
        else if (choice == 3)
        {
            cout << "Give two elements you want to union : "<<endl;
            int a,b;
            cin >> a >> b;
            ds.Union(a,b);
        }
        else if(choice == 4)
        {
            cout << "Give an element of the set: " <<endl;
            cin >> n;
            ds.Print(n);

        }
        else if(choice == 5)
        {
            break;
        }

}
return 0;
}

