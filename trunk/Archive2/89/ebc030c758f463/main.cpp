#include <iostream>


//====================================================================

class Node
{
public:

	virtual ~Node() {}

    virtual Node * clone() const = 0;

	virtual void id() const { std::cout << "Node\n"; }
};

template <typename Base>
class  InheritVirtual
    : public virtual Base
{};

template <typename... Bases>
class InheritBases
    : public Bases...
{
    virtual Node* clone() const = 0;
    virtual void id() const = 0;
};

//====================================================================

template <typename Base, typename Derived>
class NodeWrap : public Base
{
public:

	virtual Node *clone() const
	{
		return new Derived(static_cast<Derived const &>(*this));
	}
};

//====================================================================

class NodeB : public NodeWrap<InheritVirtual<Node>, NodeB>
{
public:
	NodeB() { }
	
	virtual void id() const { std::cout << "NodeB\n"; }
};

//====================================================================

class NodeC : public NodeWrap<InheritVirtual<Node>, NodeC>
{
public:
	NodeC() { }

	virtual void id() const { std::cout << "NodeC\n"; }
};

//====================================================================


class NodeD : public NodeWrap<InheritBases<NodeB,NodeC>, NodeD>
{
public:


	NodeD() { }

    virtual void id() const { std::cout << "NodeD\n"; }
};

int main()
{
	Node * b = new NodeB;
	Node * c = new NodeC;
	Node * d = new NodeD;

	b->id();
	c->id();
	d->id();

	Node * clone = b->clone();
	clone->id();
	clone = c->clone();
	clone->id();
	clone = d->clone();
	clone->id();
}