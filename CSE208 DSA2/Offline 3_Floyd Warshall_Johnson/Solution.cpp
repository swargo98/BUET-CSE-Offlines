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

class Edge
{
    int u,v;
    double weight;
public:
    Edge()
    {
        u=-1;
        v=-1;
        weight=-1;
    }
    Edge(int un, int vn, double w)
    {
        u=un;
        v=vn;
        weight=w;
    }
    int getnode()
    {
        return v;
    }
    double getweight()
    {
        return weight;
    }
    void reweight(double w)
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
    int searchItem(int item) ;
    void insertItem(int u, int v, double w) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    Edge getItem(int position) ;
    int getLength();
    void rewieght(int u,int v, double w);
    double getwieght(int u,int v);
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new Edge[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int u, int v, double w)
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

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
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

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i].getnode());
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

void ArrayList::rewieght(int u,int v, double w)
{
    int pos;
    pos= searchItem(v) ;
    if ( pos == NULL_VALUE )
    {
        insertItem(u, v, w);
        return;
    }
    list[pos].reweight(w);
}

double ArrayList::getwieght(int u,int v)
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
    double *dist;
    double **distanceMatrix;
    int **parentMatrix;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, double w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    void reweightEdge(int u, int v, double w);
    double getWeight(int u, int v);
    void printGraph();
    void floydWarshall();
    void johnsonsAlgo();
    void dijakstra(int s);
    bool bellmanford(int s);
    double getdist(int v);
    int getParent(int v);
    double getShortestPathWeight(int u ,int v);
    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void cleanSPInfo();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    color=0;
    parent=0;
    dist=0;
    distanceMatrix=0;
    parentMatrix=0;
    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;

    distanceMatrix = new double*[nVertices];
    parentMatrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        distanceMatrix[i] = new double[nVertices];
        parentMatrix[i] = new int[nVertices];
    }

}

void Graph::addEdge(int u, int v, double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    if(isEdge(u,v)) return; //vertex out of range
    this->nEdges++ ;

    adjList[u].insertItem(u,v,w) ;
    if(!directed)
    {
        adjList[v].insertItem(v,u,w) ;
        distanceMatrix[v][u]=w;
        parentMatrix[v][u]=u;
    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
    nEdges--;
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

void Graph::reweightEdge(int u, int v, double w)
{
    adjList[u].rewieght(u,v,w);
}

double Graph::getWeight(int u, int v)
{
    return adjList[u].getwieght(u,v);
}



void Graph::floydWarshall()
{
    cleanSPInfo();
    for(int i=0; i<nVertices; i++)
    {
            distanceMatrix[i][i]=0;
    }
    for(int j=0; j<(nVertices); j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                int v = adjList[j].getItem(k).getnode();
                double w = adjList[j].getItem(k).getweight();
                distanceMatrix[j][v]=w;
                parentMatrix[j][v]=j;
            }

        }
    //printDistanceMatrix();
    for(int k=0; k<nVertices; k++)
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(distanceMatrix[i][j]>distanceMatrix[i][k]+distanceMatrix[k][j])
                {
                    distanceMatrix[i][j]=distanceMatrix[i][k]+distanceMatrix[k][j];
                    parentMatrix[i][j]=parentMatrix[k][j];
                }
            }
        }
    }
}

void Graph::johnsonsAlgo()
{
    cleanSPInfo();
    Graph g2(true);
    g2.setnVertices(nVertices+1);
    for(int j=0; j<(nVertices); j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                int v = adjList[j].getItem(k).getnode();
                double w = adjList[j].getItem(k).getweight();
                g2.addEdge(j,v,w);
            }
            g2.addEdge(nVertices,j,0);
        }
    bool neg_cyc=g2.bellmanford(nVertices);
    if(neg_cyc)
    {
        cout<<"Negative Cycle Detected. No solution.\n";
        return;
    }

    double bellman_dist[nVertices+1];
    for(int i=0; i<=nVertices; i++)
        bellman_dist[i]=g2.getdist(i);
    int v;
    double w;
    for(int j=0; j<(nVertices); j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                v = adjList[j].getItem(k).getnode();
                w = g2.getWeight(j,v)+bellman_dist[j]-bellman_dist[v];
                g2.reweightEdge(j,v,w);
            }
            w = g2.getWeight(nVertices,j)-bellman_dist[j]+bellman_dist[nVertices];
            g2.reweightEdge(nVertices,j,w);
        }

    for(int j=0; j<(nVertices); j++) g2.removeEdge(nVertices,j);
    for(int j=0; j<(nVertices); j++)
    {
        g2.dijakstra(j);
        for(int k=0; k<nVertices; k++)
        {
            distanceMatrix[j][k]=g2.getdist(k)+bellman_dist[k]-bellman_dist[j];
            parentMatrix[j][k]=g2.getParent(k);
        }
    }
}

double Graph::getdist(int v)
{
    return dist[v];
}

int Graph::getParent(int v)
{
    return parent[v];
}

bool Graph::bellmanford(int s)
{
    if(s<0 || s>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return true;
    }
    dist=new double[nVertices];
    parent=new int[nVertices];
    bool neg_cyc=false;
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        parent[i]=-1;
    }

    dist[s]=0;

    for(int i=0; i<(nVertices-1); i++)
    {
        for(int j=0; j<(nVertices); j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                int v = adjList[j].getItem(k).getnode();
                double w = adjList[j].getItem(k).getweight();

                if(dist[v]>dist[j]+w)
                {
                    dist[v]=dist[j]+w;
                    parent[v]=j;
                }

            }

        }
    }

    for(int j=0; j<(nVertices); j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                int v = adjList[j].getItem(k).getnode();
                double w = adjList[j].getItem(k).getweight();

                if(dist[v]>dist[j]+w)
                {
                    neg_cyc=true;

                }

            }

        }


    return neg_cyc;

}


void Graph::dijakstra(int s)
{
    if(s<0 || s>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    dist=new double[nVertices];
    color=new int[nVertices];
    parent=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        color[i]=WHITE;
        parent[i]=-1;
    }

    priority_queue<pair<int, int> > PQ;
    dist[s]=0;
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
            if(w<0) w=-w;

            if(dist[v]>dist[cur]+w)
            {
                dist[v]=dist[cur]+w;
                PQ.push(make_pair(-dist[v],v));
                parent[v]=cur;
            }
        }


    }
}


void Graph::printGraph()
{
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            cout<<' '<<adjList[i].getItem(j).getnode()+1<<'('<<adjList[i].getItem(j).getweight()<<')';
            if(j!=(adjList[i].getLength()-1)) cout<<" -> ";
        }
        printf("\n");
    }
}

double Graph::getShortestPathWeight(int u ,int v)
{
    return distanceMatrix[u][v];
}

void Graph::printShortestPath(int u, int v)
{
    if(parentMatrix[u][v]==-1)
    {
        cout << v+1;
         return;
    }
    int p = parentMatrix[u][v];
    printShortestPath(u, p);
    cout << " --> "<< v+1 <<'('<< getWeight(p, v)<<')';
}

void Graph::printDistanceMatrix()
{
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(distanceMatrix[i][j]==INFINITY)
            {
                cout<<"INF ";
                continue;
            }
            cout<<distanceMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::printPredecessorMatrix()
{
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(parentMatrix[i][j]==-1)
            {
                cout<<"NIL ";
                continue;
            }
            cout<<parentMatrix[i][j]+1<<" ";
        }
        cout<<endl;
    }
}

void Graph::cleanSPInfo()
{
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            distanceMatrix[i][j]=INFINITY;
            parentMatrix[i][j]=-1;
        }
    }
}

Graph::~Graph()
{
    for(int i = 0; i < nVertices; i++)
    {
        delete [] distanceMatrix[i];
        delete [] parentMatrix[i];
    }
    delete [] adjList;
    delete[] color;
    delete[] parent;
    delete[] dist;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n,m,c;
    freopen("input.txt", "r", stdin); // redirects standard input
    freopen("output.txt", "w", stdout);
    cin>>n>>m;
    bool dir=true;
    Graph g(dir);
    g.setnVertices(n);
    for(int i=0; i<m; i++)
    {
        int u, v;
        double w;
        scanf("%d%d%lf", &u, &v, &w);
        g.addEdge(u-1, v-1, w);
    }
    cout<<"Graph Created"<<endl;
    while(true)
    {
        cin>>c;
        if(c==1)
        {
            g.cleanSPInfo();
            cout<<"APSP matrices cleared"<<endl;
        }
        else if(c==2)
        {
            g.floydWarshall();
            cout<<"Floyd-Warshall algorithm implemented"<<endl;
        }
        else if(c==3)
        {
            g.johnsonsAlgo();
            cout<<"Johnson’s algorithm implemented"<<endl;
        }
        else if(c==4)
        {
                int u,v;
                double w;
                cin>>u>>v;
                w=g.getShortestPathWeight(u-1,v-1);
                if(w==INFINITY)
                {
                    cout<<"No Shortest Path Exists\n";
                    continue;
                }
                cout<<"Shortest Path Weight: "<<w<<endl;
                cout<<"Path: ";
                g.printShortestPath(u-1,v-1);
                cout<<endl;
        }
        else if(c==5)
        {
            cout<<"Graph:\n";
            g.printGraph();
        }
        else if(c==6)
        {
            cout<<"Distance Matrix:\n";
            g.printDistanceMatrix();

        }
        else if(c==7)
        {
            cout<<"Predecessor Matrix:\n";
            g.printPredecessorMatrix();
        }
        else
        {
            break;
        }
    }



    return 0;

}
