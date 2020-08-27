#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<bits/stdc++.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class DisjointSet
{
    int *Parent;
    int *RankParent;
    int n;

public:
    DisjointSet(int highest_node);
    int Find_Set(int x);
    void Union(int u, int v);
    void Print(int u);
    ~DisjointSet();
};

DisjointSet::DisjointSet(int highest_node)
{
    Parent=new int[highest_node];
    RankParent=new int[highest_node];
    n=highest_node;
    for(int i=0; i<highest_node; i++)
    {
         Parent[i]=i;
         RankParent[i]=0;
    }
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

    for(int i=0; i<n; i++) if(Find_Set(i)==p) cout<<i<<' ';
    cout<<endl;
}

DisjointSet::~DisjointSet()
{
    delete Parent;
    delete RankParent;
}



class Edge
{
    int u,v;
    int weight;
public:
    Edge()
    {
        u=-1;
        v=-1;
        weight=-1;
    }
    Edge(int un, int vn, int w)
    {
        u=un;
        v=vn;
        weight=w;
    }
    int getnode()
    {
        return v;
    }
    int getweight()
    {
        return weight;
    }
    void reweight(int w)
    {
        weight=w;
    }
};

class ArrayList
{
    Edge * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    void insertItem(int u, int v, int w) ;
    Edge getItem(int position) ;
    int searchItem(int item) ;
    int getLength();
    int getwieght(int u,int v);
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new Edge[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int u, int v, int w)
{
    Edge * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
        tempList = new Edge[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = Edge(u,v,w); //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i].getnode() == item ) return i;
    }
    return NULL_VALUE;
}

Edge ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return Edge( NULL_VALUE, NULL_VALUE,  NULL_VALUE);
    return list[position];
}

int ArrayList::getLength()
{
    return length ;
}

int ArrayList::getwieght(int u,int v)
{
    int pos;
    pos= searchItem(v) ;
    if ( pos == NULL_VALUE )
    {
        return INFINITY;
    }
    return list[pos].getweight();
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    int *color;
    int *parent;
    double *key;
    priority_queue<pair<int, pair<int, int>> , vector<pair<int, pair<int, int>> >, greater<pair<int, pair<int, int>> >> DSU_PQ;
public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    bool isEdge(int u, int v);
    double getWeight(int u, int v);
    void printGraph();
    void prims_algo(int s);
    void kruskals_algo();
    double mst_weight();
    void print_prims_mst();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    color=0;
    parent=0;
    key=0;
    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    //if(isEdge(u,v)) return; //vertex out of range
    this->nEdges++ ;

    adjList[u].insertItem(u,v,w) ;
    if(!directed)
    {
        adjList[v].insertItem(v,u,w) ;
    }
    DSU_PQ.push(make_pair(w,make_pair(u,v)));
}



bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return false;
    }
    if(adjList[u].searchItem(v) == NULL_VALUE) return false;
    return true;


}


double Graph::getWeight(int u, int v)
{
    return adjList[u].getwieght(u,v);
}



void Graph::prims_algo(int s)
{
    if(s<0 || s>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }

    key=new double[nVertices];
    color=new int[nVertices];
    parent=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        key[i]=INFINITY;
        color[i]=WHITE;
        parent[i]=-1;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > PQ;
    key[s]=0;
    PQ.push(make_pair(0,s));

    while(!PQ.empty())
    {
        int cur=PQ.top().second;
        PQ.pop();

        if(color[cur]==BLACK) continue;
        color[cur]=BLACK;

        for(int i=0; i<adjList[cur].getLength(); i++)
        {
            int v = adjList[cur].getItem(i).getnode();
            double w = adjList[cur].getItem(i).getweight();

            if(color[v]==WHITE && key[v]>w)
            {
                key[v]=w;
                PQ.push(make_pair(key[v],v));
                parent[v]=cur;
            }
        }


    }
}

double Graph::mst_weight()
{
    double sum=0;
    for(int i=0; i<nVertices; i++) sum+=key[i];
    return sum;
}

void Graph::print_prims_mst()
{
    for(int i=0; i<nVertices; i++)
    {
        if(parent[i]!=-1)
            cout<<i<<' '<<parent[i]<<endl;
    }
}

void Graph::kruskals_algo()
{
    DisjointSet dsu(nVertices);
    cout<<"Kruskal's Algorithm:\n";
    for(int i=0; i<nEdges; i++)
    {
        int u=DSU_PQ.top().second.first;
        int v=DSU_PQ.top().second.second;
        if(dsu.Find_Set(u)!=dsu.Find_Set(v))
        {
            cout<<u<<' '<<v<<endl;
            dsu.Union(u,v);
        }
        DSU_PQ.pop();
    }
}

void Graph::printGraph()
{
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            cout<<' '<<adjList[i].getItem(j).getnode()<<'('<<adjList[i].getItem(j).getweight()<<')';
            if(j!=(adjList[i].getLength()-1)) cout<<" -> ";
        }
        printf("\n");
    }
}


Graph::~Graph()
{
    delete [] adjList;
    delete[] color;
    delete[] parent;
    delete[] key;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n,m,c,root=0;
    freopen("input.txt", "r", stdin); // redirects standard input
    freopen("output.txt", "w", stdout);
    cin>>n>>m;
    bool dir=false;
    Graph g(dir);
    g.setnVertices(n);
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addEdge(u, v, w);
    }
    g.prims_algo(root);
    cout<<g.mst_weight()<<endl;
    g.kruskals_algo();
    cout<<"Prim's Algorithom:"<<endl;
    cout<<"Root node = "<<root<<endl;
    g.print_prims_mst();
    return 0;

}
