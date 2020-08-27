#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<iostream>
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
    rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;
    int *color;
    int *parent;
    int *dist;
    //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u, bool out = true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
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

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
    nEdges++;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }

    matrix[u][v]=0;
    if(!directed) matrix[v][u]=0;
    nEdges--;
    return;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return false;
    }
    if(matrix[u][v]==0) return false;
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
    int deg=0;
    if(out==true)
    {
        for(int i=0; i<nVertices; i++)
            if(matrix[u][i]==1) deg++;
        return deg;
    }

    for(int i=0; i<nVertices; i++)
            if(matrix[i][u]==1) deg++;

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

    for(int i=0; i<nVertices; i++)
        if(matrix[u][i]==1) cout<<i<<" ";
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return false;
    }
    for(int i=0; i<nVertices; i++)
    {

        if(matrix[u][i]==1 && matrix[v][i]==1) return true;

    }

    return false;

}

void Graph::bfs(int source)
{
    //write this function
    if(source<0 || source>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        dist[i]=INFINITY;
        parent[i]=-1;
    }

    Queue q;
    int s;
    //color[source]=GREY;
    q.enqueue(source);
    dist[source]=0;
    parent[source]=-1;

    while(!q.empty())
    {
        s=q.dequeue();
        color[s]=GREY;
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[s][i]==1 && color[i]==WHITE)
            {
                parent[i]=s;
                dist[i]=dist[s]+1;
                q.enqueue(i);
            }
        }
        color[s]=BLACK;
    }

}

int Graph::getDist(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return -1;
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
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    for(int i = 0; i < nVertices; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
    delete[] color;
    delete[] parent;
    delete[] dist;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
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
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
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
    }

}

