#include<iostream>
#include <list>

using namespace std;

class Graph
{
    int E;
	list <int> *adj;
	void DFSUtil (int e, bool visited[]);
    public:
    
	Graph (int E);
	void addEdge (int e, int f);
	void DFS (int e);
};

Graph::Graph (int E)
{
	this -> E = E;
	adj = new list <int> [E];
}

void Graph::addEdge (int e, int f)
{
	adj[e].push_back(f);
}

void Graph::DFSUtil (int e, bool visited[])
{

	visited [e] = true;
	cout << e << " ";

	list<int>::iterator i;
	for (i = adj[e].begin(); i != adj[e].end(); ++i)
		if (!visited[*i])
			DFSUtil (*i, visited);
}

void Graph::DFS (int e)
{
	bool *visited = new bool[E];
	for (int i = 0; i < E; i++)
		visited[i] = false;
	DFSUtil(e, visited);
}

int main()
{
	Graph a(9);
	a.addEdge(1, 2);
	a.addEdge(1, 3);
	a.addEdge(2, 1);
	a.addEdge(2, 4);
	a.addEdge(2, 5);
	a.addEdge(3, 1);
	a.addEdge(3, 6);
	a.addEdge(3, 7);
	a.addEdge(4, 2);
	a.addEdge(4, 8);
	a.addEdge(5, 2);
	a.addEdge(5, 8);
	a.addEdge(6, 3);
	a.addEdge(6, 8);
	a.addEdge(7, 3);
	a.addEdge(7, 8);
	a.addEdge(8, 4);
	a.addEdge(8, 5);
	a.addEdge(8, 6);
	a.addEdge(8, 7);


	cout << "Depth First Traversal \n";
	a.DFS(1);

	system("Pause");
}




