#include <iostream>
#include <vector>
#include <utility>

class SomethingHandler
{
public: 
    SomethingHandler() {}
	~SomethingHandler() {}

	virtual void handleSomething(int something)
	{
		doHandleSomething(something);
	}

private:
	virtual void doHandleSomething(int something) = 0;
	
};

class Router
{
public:
	Router() {}
	
	void registerHandlerForSomething(int somethingInteresting, SomethingHandler* h)
	{
		m_handler.push_back(std::pair<int,SomethingHandler*> (somethingInteresting, h));
	}
	
	void receive(int something) const
	{
		for(unsigned int i=0; i < m_handler.size(); ++i)
		{
			if(m_handler.at(i).first == something)
			{
				if(m_handler.at(i).second)
				{
					m_handler.at(i).second->handleSomething(something);
				}
			}
		}
	}
	
private:
	std::vector< std::pair<int,SomethingHandler*> > m_handler;
};

class aHandler : public SomethingHandler
{
public:
	aHandler() {}
private:
	void doHandleSomething(int something) 
	{
		std::cout << "handled something: " << something << "\n";
	}
};

int main()
{
	Router r;
	aHandler h;
	
	r.registerHandlerForSomething(42, &h);
	
	r.receive(42);
}