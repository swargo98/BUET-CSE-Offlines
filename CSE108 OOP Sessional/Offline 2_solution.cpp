#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

class stack
{
    int len=0, cnt=0;
    int* stc;
public:
    stack()
    {
        len+=10;
        stc= new int [10];
        if(!stc) cout<<"Allocation Failed."<<endl;
        else cout<<"Successfully Constructed with Constructor 1"<<endl;
    }

    stack(int n)
    {
        len+=n;
        stc= new int[n];
        if(!stc) cout<<"Allocation Failed."<<endl;
        else cout<<"Successfully Constructed with Constructor 2"<<endl;
    }
    stack(const stack &n)
    {
        len=n.len;
        cnt=n.cnt;
        stc=new int[len];
        if(!stc) cout<<"Allocation Failed."<<endl;
        else cout<<"Successfully Constructed with Constructor 3"<<endl;
        for(int i=0; i<cnt; i++)
        {
            stc[i]=n.stc[i];
        }

    }
    ~stack()
    {
        cout<<"Destructed"<<endl;
        delete []stc;
    }

    void push(int n)
    {
        stc=(int*) realloc(stc,sizeof(int)*(cnt+1));
        stc[cnt++]=n;
    }

    void push(int* n, int size)
    {
        for(int j=0; j<size; j++)
        {
            stc=(int*) realloc(stc,sizeof(int)*(cnt+1));
            stc[cnt++]=*(n+j);
        }
    }

    void push(stack a)
    {
        int sz=a.size();
        cout<<sz<<endl;
        for(int j=0; j<sz; j++)
        {
            stc=(int*) realloc(stc,sizeof(int)*(cnt+1));
            stc[cnt++]=a.pop();
        }

    }

    int pop()
    {
        if(cnt==0)
        {
            cout<<"Empty Stack"<<endl;
            return -1;
        }
        int k=stc[--cnt];
        stc=(int*) realloc(stc,cnt*sizeof(int));
        return k;

    }

    float similarity(stack b)
    {
        int as,bs, simcnt=0;
        float avg;
        as=cnt;
        bs=b.cnt;
        avg=(as+bs)/2.0;
        //int s=(as>bs)? bs:as;
        for(int i =as-1, j=bs-1 ; i>=0, j>=0 ; i--, j--)
        {

                if(b.stc[j]==stc[i])
                {
                    simcnt++;
                }


        }

        return simcnt/avg;
    }

    int top()
    {
        if(cnt==0)
        {
            cout<<"Empty Stack"<<endl;
            return -1;
        }
        return stc[cnt-1];
    }

    int size()
    {
        return cnt;
    }



};

int main()
{
    stack a;
    int n,k;

    while(1)
    {
        printf("Press a button:\n1: Push an element\t5: Top\n2: Push an array\t6: Size\n3: Push a stack\t\t7: Similarity\n4: Pop\t\t\t8: Exit\n");
        cin>>n;
        if(n==1)
        {
            printf("Enter a number:\n");
            cin>>k;
            a.push(k);
        }
        else if(n==2)
        {
            int noe;
            int* ar;
            cout<<"The number of elements:"<<endl;
            cin>>noe;
            cout<<"Enter the elements:"<<endl;
            ar=new int[noe];
            for(int j=0; j<noe; j++) cin>>*(ar+j);
            a.push(ar,noe);
            delete []ar;
        }
        else if(n==3)
        {
            int noe,t;
            cout<<"The number of elements:"<<endl;
            cin>>noe;
            cout<<"Enter the elements:"<<endl;
            stack b;
            for(int i=0; i<noe; i++)
            {
                cin>>t;
                b.push(t);
            }
            a.push(b);
        }
        else if(n==4)
        {
            cout<<"The popped element: ";
            cout<<a.pop()<<endl;
        }
        else if(n==5)
        {
            cout<<"The last/top element: ";
            cout<<a.top()<<endl;
        }
        else if(n==6)
        {
            cout<<"Stack size: ";
            cout<<a.size()<<endl;
        }
        else if(n==7)
        {
            int noe,t;
            cout<<"The number of elements: ";
            cin>>noe;
            cout<<"Enter the elements:"<<endl;
            stack b;
            for(int i=0; i<noe; i++)
            {
                cin>>t;
                b.push(t);
            }

            cout<<a.similarity(b)<<endl;
        }
        else if(n==8)
        {
            int k=a.size();
            cout<<"The elements of the stack:"<<endl;
            for(int i=0; i<k; i++) cout<<a.pop()<<" ";
            cout<<endl;
            return 0;
        }


    }
}

