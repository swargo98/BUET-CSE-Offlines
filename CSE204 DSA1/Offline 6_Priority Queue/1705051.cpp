#include<bits/stdc++.h>

using namespace std;

class max_heap
{
protected:
    int* heap;
    int heap_size;
    int heap_capacity;
    max_heap();
    max_heap(int ar[], int s);
    int left(int i);
    int right(int i);
    int parent(int i);
    void max_heapify(int i);
    void increase_key(int i, int key);
    void decrease_key(int i, int key);
    void insert_node(int node);
    void show();
    int extract_max();
    ~max_heap()
    {
        free(heap);
        //cout<<"Destroyed"<<endl;
    }

};
max_heap::max_heap(int ar[],int s)
{
    int i;
    heap=new int[s+1];
    heap_size=s;
    heap[0]=0;
    for(i=1; i<s+1; i++)
    {
        heap[i]=ar[i];
    }
    for(i=s/2; i>=1; i--)
    {
        max_heapify(i);
    }
}

max_heap::max_heap()
{

    heap_size=0;
    heap_capacity=10;
    heap=(int*) malloc((heap_capacity+1)*sizeof(int));
    heap[0]=0;
    //cout<<"Constructed"<<endl;
}
int max_heap::left(int i)
{
    return 2*i;
}
int max_heap::right(int i)
{
    return 2*i+1;
}
int max_heap::parent(int i)
{
    return i/2;
}
void max_heap::max_heapify(int i)
{
    int l,r,largest,t;
    l=left(i);
    r=right(i);

    if(l<=heap_size && heap[l]>heap[i]) largest=l;
    else largest=i;
    if(r<=heap_size && heap[r]>heap[largest]) largest=r;
    //cout<<"Largest: "<<largest<<endl;
    if(largest!=i)
    {
        t=heap[i];
        heap[i]=heap[largest];
        heap[largest]=t;
        //cout<<"Max Heapify er vitore: "<<i<<endl;
        max_heapify(largest);
    }
}

void max_heap::increase_key(int i, int key)
{
    int p,t;
    if(key<heap[i])
    {
        cout<<"New key is smaller";
        return;
    }
    if(i>heap_size || i<1)
    {
        cout<<"Invalid Index";
        return;
    }
    heap[i]=key;
    while(i>1 && heap[i]>heap[parent(i)])
    {
        p=parent(i);
        t=heap[p];
        heap[p]=heap[i];
        heap[i]=t;
        i=p;
    }
}
void max_heap::decrease_key(int i, int key)
{
    int p,t;
    if(key>heap[i])
    {
        cout<<"New key is larger";
        return;
    }
    if(i>heap_size || i<1)
    {
        cout<<"Invalid Index";
        return;
    }
    heap[i]=key;
    max_heapify(i);
}

void max_heap::insert_node(int node)
{
    int i,p,t;
    heap_size++;
    if(heap_size%10==1)
    {
        heap_capacity+=10;
        heap=(int*) realloc(heap, sizeof(int)*(heap_capacity+1));
    }
    heap[heap_size]=node;
    /*i=heap_size;
    while(i>1 && heap[i]>heap[parent(i)])
    {
        p=parent(i);
        t=heap[p];
        heap[p]=heap[i];
        heap[i]=t;
        i=p;
    }*/
    increase_key(heap_size, node);
}

int max_heap::extract_max()
{
    //cout<<heap_size<<endl;
    if(heap_size==0)
    {
        cout<<"Empty Priority Queue";
        return -1;
    }
    int max_item=heap[1];
    heap[1]=heap[heap_size];

    heap_size--;
    //cout<<heap_size<<endl;
    max_heapify(1);
    //cout<<heap_size<<endl;
    //heap=(int*) realloc(heap, sizeof(int)*(heap_size+1));
    return max_item;
}

void max_heap::show()
{
    if(heap_size==0)
    {
        cout<<"Empty Priority Queue"<<endl;
        return;
    }
    for(int i=1; i<=heap_size; i++) cout<<heap[i]<<' ';
    cout<<endl;
}

class my_priority_queue: public max_heap
{
public:
    my_priority_queue()
    {

    }
    my_priority_queue(int ar[], int s):max_heap(ar,s)
    {

    }
    void Insert(int x);
    int FindMax();
    int ExtractMax();
    void IncreaseKey(int i, int NewKey);
    void DecreaseKey(int i, int NewKey);
    void Print();
};
void my_priority_queue::Insert(int x)
{
    insert_node(x);
}
int my_priority_queue::FindMax()
{
    return heap[1];
}
int my_priority_queue::ExtractMax()
{
    return extract_max();
}
void my_priority_queue::IncreaseKey(int i, int NewKey)
{
    increase_key(i,NewKey);
}
void my_priority_queue::DecreaseKey(int i, int NewKey)
{
    decrease_key(i,NewKey);
}
void my_priority_queue::Print()
{
    show();
}
int main()
{
    my_priority_queue h;
    int n, a, b;

    while(1){
        cout<<"1. Insert an Integer\n";
        cout<<"2. Find the Maximum Element\n";
        cout<<"3. Extract the Maximum Element\n";
        cout<<"4. Increase a Key\n";
        cout<<"5. Decrease a Key\n";
        cout<<"6. Print Heap\n";
        cout<<"7. Exit\n";

        cin>>n;

        if(n == 1){
            cin>>a;
            h.Insert(a);
        }

        else if(n == 2){
            cout<<h.FindMax()<<endl;
        }

        else if(n == 3){
            cout<<h.ExtractMax()<<endl;
        }

        else if(n == 4){
            cin>>a>>b;
            h.IncreaseKey(a, b);
        }

        else if(n == 5){
            cin>>a>>b;
            h.DecreaseKey(a, b);
        }

        else if(n == 6){
            h.Print();
        }
        else if(n ==7){
            break;
        }
    }
    return 0;
}

/*
1
1
1
10
1
1000
1
10000
6
2
6
3
6
4
3 100000
6
5
1 5
6
7
*/
