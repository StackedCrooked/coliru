#include <iostream>
#include <stack>
#include <unordered_set>
#include <map>
#include <vector>

using namespace std;

struct X
{
    int i;
    X () { cout << "X ctor this address: " << this << endl; }
    ~X () { cout << "X dtor this address: " << this << endl; }
    X & ref() { cout << "X ref this address: " << this << " i = " << i << endl; return *this; }
    int & get () { cout << "X get this address: " << this << " i = " << i << endl; return i; }
    void print () { cout << "X print this address: " << this << " i = " << i << endl; }
};

struct Node
{
  int d;
  Node *np;
  Node() : d(0), np(nullptr) { }
};

bool IsCyclic (Node * np)
{
    unordered_set<Node*> h;
	bool bRet = false;

	while(! bRet && np != nullptr)
	{
		bRet = h.find(np) != h.end();
		if (! bRet)
		{
			h.insert(np);
			np = np->np;
		}
	}
	return bRet;
}

void rev5(Node * np)
{
  // queue to hold the 5 nodes before the last node
  deque<Node *> q;

  // load queue
  while (np->np != nullptr)
  {
    q.push_front(np);
    if (q.size() > 5) q.pop_back();
    np = np->np;
  }

  // hold original end node to attach to stub
  Node * npend = np;
  
  int i = 0;
  // reverse last five or less
  while (! q.empty() && i < 4)
  {
    np->np = q.front();
    q.pop_front();
    np = np->np;
    ++i;
  }

  // terminate new end node
  np->np = nullptr;

  // if queue not empty, had length 5
  // attach beg of reversed list to end of stub 
  if (! q.empty())
  {
    q.front()->np = npend;
    q.pop_front();
  }
}

// test bench

int main()
{
    unsigned i = 1;
    const unsigned len = 9;
    Node * const npbeg = new Node, * np;
    np = npbeg;
    while (i < len)
    {
        np->np = new Node;
        np = np->np;
        np->d = i;
        ++i;
    }
    Node *npend = np;
    np = npbeg;
    while (np != nullptr)
    {
        cout << np << " " << np->d << " " << np->np << endl;
        np = np->np;
    }

    cout << endl;
    np = npbeg;
    rev5(np);

    np = len > 5 ? npbeg : npend;

    while (np != nullptr)
    {
        cout << np << " " << np->d << " " << np->np << endl;
        np = np->np;
    }
    return 0;
}

/*
int main()
{
    Node * const npbeg = new Node, * np;
    unsigned i = 1;
    vector<Node*> v;
    np = npbeg;
    v.push_back(np);
    while (i < 10)
    {
        np->np = new Node;
        np = np->np;
        np->d = i;
        v.push_back(np);
        ++i;
    }
    np = npbeg;
    while (np != nullptr)
    {
        cout << np << " " << np->d << " " << np->np << endl;
        np = np->np;
    }

    cout << endl << "Is Cyclic: " << IsCyclic(npbeg);
    
    // make cyclic
    v[9]->np = v[5];

    cout << endl << "Is Cyclic: " << IsCyclic(npbeg);


    // clean up
    for (Node * np : v) delete np;
    return 0;
}
*/