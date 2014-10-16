#include <memory>
#include <queue>
#include <vector>
#include <string>
#include <limits>
#include <iostream>
using namespace std;

struct Node
{
    vector<shared_ptr<Node>> links;
	string name;
	unsigned int nbShortestPaths;
	unsigned int shortestPathLength;
	Node(string name) : name(name), nbShortestPaths(0), shortestPathLength(numeric_limits<unsigned int>::max()) {}
};

int countShortestPaths(shared_ptr<Node> from, shared_ptr<Node> to)
{
	if (!from || !to) return 0;

	bool shortestPathFound = false;

	queue<shared_ptr<Node>> q;
	from->shortestPathLength = 0;
	from->nbShortestPaths = 1;
	q.push(from);

	while (!q.empty()) {
		auto current = q.front(); q.pop();

		for (auto link : current->links) {

			if (link->nbShortestPaths == 0 && !shortestPathFound) {
				q.push(link);
				link->shortestPathLength = current->shortestPathLength + 1;
				shortestPathFound = link == to;
			}
			
			if (link->shortestPathLength == current->shortestPathLength + 1) {
				link->nbShortestPaths += current->nbShortestPaths;
			}
		}
	}

	return to->nbShortestPaths;
}


int main()
{
	shared_ptr<Node> A = make_shared<Node>("A");
	shared_ptr<Node> B = make_shared<Node>("B");
	shared_ptr<Node> C = make_shared<Node>("C");
	shared_ptr<Node> D = make_shared<Node>("D");
	shared_ptr<Node> E = make_shared<Node>("E");
	shared_ptr<Node> F = make_shared<Node>("F");
	shared_ptr<Node> G = make_shared<Node>("G");
	shared_ptr<Node> H = make_shared<Node>("H");
	shared_ptr<Node> I = make_shared<Node>("I");

	A->links = {G, B, E};
	B->links = {C};
	C->links = { D };
	E->links = {C, F};
	F->links = {C, D, I};
	G->links = { H, C };
	H->links = {C, D};
	I->links = {D};

	cout << countShortestPaths(A, C) << endl;
    
    return 0;
}