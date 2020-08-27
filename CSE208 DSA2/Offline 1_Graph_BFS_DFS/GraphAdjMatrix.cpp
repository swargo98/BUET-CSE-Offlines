#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include <iomanip>
#include<chrono>

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
    int time;
    int *start;
    int *finish;
    void dfs_visit(int s);
    //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source, bool print=false);
    void dfs(int source); //will run bfs in the graph
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
    time=0;
    start=0;
    finish=0;
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

bool Graph::addEdge(int u, int v)
{
    //write your code here
    if(isEdge(u,v)) return false;
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
    nEdges++;
    return true;
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

int Graph::getInDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return -1;
    }
    int deg=0;
    for(int i=0; i<nVertices; i++)
        if(matrix[i][u]==1) deg++;

    return deg;
}

int Graph::getOutDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return -1;
    }
    int deg=0;

    for(int i=0; i<nVertices; i++)
        if(matrix[u][i]==1) deg++;
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

void Graph::bfs(int source, bool print)
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
        if(print)cout<<s<<' ';
        color[s]=GREY;
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[s][i]==1 && color[i]==WHITE)
            {
                color[i]=GREY;
                parent[i]=s;
                dist[i]=dist[s]+1;
                q.enqueue(i);
            }
        }
        color[s]=BLACK;
    }

}

void Graph::dfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    if(source<0 || source>=nVertices)
    {
        cout<<"Invalid Vertex"<<endl;
        return;
    }
    color=new int[nVertices];
    start=new int[nVertices];
    finish=new int[nVertices];
    time=0;
    for(int i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        //parent[i]=-1;
        start[i]=INFINITY;
        finish[i]=INFINITY;
    }
    dfs_visit(source);
}

void Graph::dfs_visit(int s)
{
    //write this function
    cout<<s<<' ';
    color[s]=GREY;
    time++;
    start[s]=time;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[s][i]==1 && color[i]==WHITE)
        {
            dfs_visit(i);
        }
    }
    color[s]=BLACK;
    time++;
    finish[s]=time;

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
        cout<<"7. Graph Traversal\n";
        cout<<"8. Get shortest path distance of two vertices\n";
        cout<<"9. Print Graph\n";
        cout<<"10. Runtime Analysis\n";
        cout<<"11. Exit\n";
        //printf("4. (Add from homework). 5. Print Graph  6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.addEdge(u, v)) cout<<"Edge Added\n";
            else cout<<"Error\n";
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
        else if(ch == 4)
        {
            cout<<"Vertex: ";
            cin>>u;
            cout<<"1.In Degree\n2.Out Degree\n";
            int op;
            cin>>op;
            if(op==1) cout<<g.getInDegree(u)<<endl;
            if(op==2) cout<<g.getOutDegree(u)<<endl;
        }
        else if(ch == 5)
        {
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch == 6)
        {
            cin>>u>>v;
            cout<<g.hasCommonAdjacent(u, v)<<endl;
        }
        else if(ch == 7)
        {
            cout<<"Vertex: ";
            cin>>u;
            cout<<"1.BFS\n2.DFS\n";
            int op;
            cin>>op;
            if(op==1)
            {
                g.bfs(u, true);
                cout<<endl;
            }
            if(op==2)
            {
                g.dfs(u);
                cout<<endl;
            }

        }
        else if(ch == 8)
        {
            cin>>u>>v;
            cout<<g.getDist(u, v)<<endl;
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            srand(time(0));

            int ver;
            int choice2;
            bool dir2;
            printf("Enter your choice:\n");
            printf("1. directed graph   2. undirected graph\n");
            scanf("%d",&choice2);
            if(choice == 1)dir2 = true;
            else if(choice == 2)dir2 = false;

            //Graph g2(dir2);
            printf("Enter number of vertices: ");
            scanf("%d", &ver);

            double t_sum, t_avg;
            //cout<<"Number of vertices: ";
            long long edge,mult=1;
            int v1,v2,src;
            //cin>>ver;
            while(true)
            {
                Graph g2(dir2);
                g2.setnVertices(ver);
                edge=mult*ver;
                //cout<<edge<<endl;
                if(edge>(ver*(ver-1))/8) break;
                //if(edge>128000) break;
                //if(edge>50) break;
                mult*=2;
                //cout<<mult<<endl;
                for(int i=0; i<edge; i++)
                {
                    v1=rand()%ver;
                    v2=rand()%ver;
                    //cout<<v1<<' '<<v2<<endl;
                    if(g2.isEdge(v1,v2))
                    {
                        i--;
                        continue;
                        //g2.printGraph();
                        //break;
                    }
                    g2.addEdge(v1,v2);
                }
                int it=10;
                for(int j=0; j<it; j++)
                {
                    src=rand()%ver;

                    auto start = chrono::steady_clock::now();

                    g2.bfs(src);

                    auto end = chrono::steady_clock::now();

                    double time_taken_bfs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();


                    t_sum+=time_taken_bfs/it;
                }
                //g2.printGraph();
                cout<<"For number of edges: "<<edge<<", average BFS time: "<< fixed << t_sum/(1000)<<endl;
                //g2=0;
                t_sum=0;

            }
            //break;

        }
        else if(ch==11)
        {
            break;
        }
    }

}

