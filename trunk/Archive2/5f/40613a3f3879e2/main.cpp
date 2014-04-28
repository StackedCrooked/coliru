#include <iostream>

using namespace std;

class unorderedMaxPQ

{

public:

    int *pq;
    int N;

    unorderedMaxPQ(int capacity)
   {
        pq = new int[capacity];
   }

    ~unorderedMaxPQ()
    {
        N=0;
    }
    bool isEmpty()
    {
        if (N == 0)
            return true;
    }
    void enqueue(int x)
    {
        pq[N++]=x;
    }

    int dequeue()
    {
        int M = 0;
        for(int i = 1;i < N; i++)
        if (pq[M] < pq[i]) M = i;
        int temp = pq[M];
        pq[M]= pq[N-1];
        pq[N-1] = temp;
        return pq[--N];
    }

    void print()
    {
        for (int i = 0; i < N; i++)
            cout<<pq[i]<<" ";
        cout<<endl;
    }
};

int main() {}