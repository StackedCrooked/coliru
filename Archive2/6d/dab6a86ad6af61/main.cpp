#include<iostream>
#include <list>

using namespace std;


class Graph
{
    int E;    
	list<int> *adj;    
    public:
	Graph(int E);  
	void addEdge(int e, int f); 
	void BFS(int b);  
};

Graph::Graph(int E)
{
	this-> E = E;
	adj = new list<int>[E];
}

void Graph::addEdge(int e, int f)
{
	adj[e].push_back(f); 
}

void Graph::BFS(int b)
{
	
	bool *visited = new bool[E];
	for (int i = 0; i < E; i++)
		visited[i] = false;

	
	list<int> queue;

	
	visited[b] = true;
	queue.push_back(b);

	
	list<int>::iterator i;

	while (!queue.empty())
	{
		
		b = queue.front();
		cout << b << " ";
		queue.pop_front();

		
		for (i = adj[b].begin(); i != adj[b].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}
int main()
{
	
	Graph a (8);
	a.addEdge (1, 2);
	a.addEdge (1, 3);
	a.addEdge (2, 1);
	a.addEdge (2, 4);
	a.addEdge (2, 5);
	a.addEdge (3, 1);
	a.addEdge (3, 6);
	a.addEdge (3, 7);
	a.addEdge (4, 2);
	a.addEdge (4, 8);
	a.addEdge (5, 2);
	a.addEdge (5, 8);
	a.addEdge (6, 3);
	a.addEdge (6, 8);
	a.addEdge (7, 3);
	a.addEdge (7, 8);
    a.addEdge (8, 4);
	a.addEdge (8, 5);
	a.addEdge (8, 6);
	a.addEdge (8, 7);



	cout << "BREATH First Traversal \n";
	a.BFS (1);

	system("Pause");
}








