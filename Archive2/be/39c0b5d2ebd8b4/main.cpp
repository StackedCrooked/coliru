#include <iostream>
#include <algorithm>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <iterator>
#include <numeric>
#include <functional>

class Node;
class Graph_Container
{
public:
    std::shared_ptr<Node> operator[](int id)
	{
		return nodes_[id];
	}
	std::map<int, std::shared_ptr<Node>> nodes_;
};
class Node
{
public:
	Node(Graph_Container* container, int id) :
		id_(id), container_(container)
	{}
	void addAdjNode(int id)
	{
		auto it = container_->nodes_.find(id);
		if (it == container_->nodes_.end())//if not found first add it
			(container_->nodes_)[id] = std::make_shared<Node>(new Node(container_, id));
		adjNodes_.push_back(container_->nodes_[id]);
	}
	std::vector<std::shared_ptr<Node>> adjNodes_;
private:
	int id_;
	Graph_Container* container_;
};

class Graph
{
public:
	void addNode(int id, bool directed = false)
	{
		container_[id] = std::make_shared<Node>(new Node(this->container(), id));
		directed_ = directed;
	}
	std::shared_ptr<Node> operator[](int id)
	{
		return container_[id];
	}
	bool isDirected()
	{
		return directed_;
	}
	Graph_Container* container()
	{
		return &container_;
	}
private:
	bool directed_;
	Graph_Container container_;
};


int main()
{
	Graph g;

	g.addNode(1);
	g.addNode(2);
	g.addNode(3);
	g.addNode(4);

	//g[1]->addAdjNode(3);
}