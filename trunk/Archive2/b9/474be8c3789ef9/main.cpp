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
class Container
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
	Node(Container* container, int id)
	{

	}
private:
	Container* container_;
};
class Test
{
public:
	void addNode(int id)
	{
		container_[id] = std::make_shared<Node>(new Node(&container_, id));
	}
	std::shared_ptr<Node> operator[](int id)
	{
		return container_[id];
	}
private:
	Container container_;
};
int main()
{
	Test t;
	t.addNode(5);
}