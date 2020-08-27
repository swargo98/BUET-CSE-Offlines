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

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************

class Edge
{
    int node, weight;
public:
    Edge()
    {
        node=-1;
        weight=-1;
    }
    Edge(int n, int w)
    {
        node=n;
        weight=w;
    }
    int getnode()
    {
        return node;
    }
    int getweight()
    {
        return weight;
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
    void insertItem(int item, int w) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    Edge getItem(int position) ;
    int getLength();
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

void ArrayList::insertItem(int newitem, int w)
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

    list[length] = Edge(newitem,w); //store new item
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
    if(position < 0 || position >= length) return Edge( NULL_VALUE,  NULL_VALUE);
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
    int *dist;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u, bool out= true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dijakstra(int s, int d);
    void bellmanford(int s, int d);
    void printpath(int d);

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
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v,w) ;
    if(!directed) adjList[v].insertItem(u,w) ;
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

int Graph::getDegree(int u, bool out)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return -1;
    }
    if(out) return adjList[u].getLength();

    int deg=0;
    for(int i=0; i<nVertices; i++)
        if(adjList[i].searchItem(u)!= NULL_VALUE) deg++;
    return deg;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    adjList[u].printList();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return false;
    }
    for(int i=0; i<adjList[u].getLength(); i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i).getnode())!= NULL_VALUE) return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    if(source<0 || source>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    dist=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
    }

    Queue q;
    int s;
    //color[source]=GREY;
    q.enqueue(source);
    dist[source]=0;
    while(!q.empty())
    {
        cout<<"Aise re!!";
        s=q.dequeue();
        for(int i=0; i<adjList[s].getLength(); i++)
        {
            if(dist[s]+adjList[s].getItem(i).getweight()<dist[adjList[s].getItem(i).getnode()])
            {
                dist[adjList[s].getItem(i).getnode()]=dist[s]+adjList[s].getItem(i).getweight();
                q.enqueue(adjList[s].getItem(i).getnode());

            }

        }
    }

}


void Graph::printpath(int d)
{
    if(parent[d] == -1)
    {
         cout<<d;
         return;
    }

    printpath(parent[d]);
    cout << " -> " << d;
}

void Graph::bellmanford(int s, int d)
{
    if(s<0 || s>=nVertices || d<0 || d>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    dist=new int[nVertices];
    color=new int[nVertices];
    parent=new int[nVertices];
    bool neg_cyc;
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        //color[i]=WHITE;
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
                int w = adjList[j].getItem(k).getweight();

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
                int w = adjList[j].getItem(k).getweight();

                if(dist[v]>dist[j]+w)
                {
                    cout<<"Negative Cycle Detected. No Solution.\n";
                    neg_cyc=true;

                }

            }

        }

    if(!neg_cyc)
    {
         cout<<dist[d]<<endl;
         printpath(d);
         cout<<endl;
    }

}


void Graph::dijakstra(int s, int d)
{
    if(s<0 || s>=nVertices || d<0 || d>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    dist=new int[nVertices];
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
            int w = adjList[cur].getItem(i).getweight();
            if(w<0) w=-w;

            if(dist[v]>dist[cur]+w)
            {
                dist[v]=dist[cur]+w;
                PQ.push(make_pair(-dist[v],v));
                parent[v]=cur;
            }
        }


    }

    if(dist[d]==INFINITY) cout<<"-1"<<endl;
    else
    {
        cout<<dist[d]<<endl;
        printpath(d);
        cout<<endl;
    }
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return false;
    }
    this->bfs(u);
    return dist[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    delete [] adjList;
    delete[] color;
    delete[] parent;
    delete[] dist;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n,m,s,d;
    freopen("input.txt", "r", stdin); // redirects standard input
    freopen("output.txt", "w", stdout);
    cin>>n>>m;
    bool dir=true;
    Graph g(dir);
    g.setnVertices(n);
    for(int i=0; i<m; i++)
    {
        int u, v,w;
        scanf("%d%d%d", &u, &v, &w);
        g.addEdge(u, v, w);
    }
    cin>>s>>d;
    //g.printGraph();
    cout<<"Bellman Ford Algorithm:\n";

    g.bellmanford(s,d);

    cout<<"Dijakstra Algorithm:\n";

    g.dijakstra(s,d);

    return 0;

}

/*
int n, u, v;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        cout<<"2. Remove edge\n";
        cout<<"3. Check whether there is an edge between two vertex\n";
        cout<<"4. Get degree of a vertex\n";
        cout<<"5. Print Adjacent vertices of a vertex\n";
        cout<<"6. Check whether two vertices have same edge\n";
        cout<<"7. Bfs\n";
        cout<<"8. Get shortest path distance of two vertices\n";
        cout<<"9. Print Graph\n";
        cout<<"10. Exit\n";
        //printf("4. (Add from homework). 5. Print Graph  6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v,w;
            scanf("%d%d%d", &u, &v, &w);
            g.addEdge(u, v, w);
        }
        else if(ch==2)
        {
            cin>>u>>v;
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            cin>>u>>v;
            cout<<g.isEdge(u, v)<<endl;
        }
        else if(ch == 4){
            cin>>u;
            cout<<g.getDegree(u)<<endl;
        }
        else if(ch == 5){
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch == 6){
            cin>>u>>v;
            cout<<g.hasCommonAdjacent(u, v)<<endl;
        }
        else if(ch == 7){
            cin>>u;
            g.bfs(u);
        }
        else if(ch == 8){
            cin>>u>>v;
            cout<<g.getDist(u, v)<<endl;
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }*/
