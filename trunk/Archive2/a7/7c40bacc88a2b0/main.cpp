#include <iostream>
#include <functional>
#include <memory>
#include <string>

class Obj
{
public:
    int v;

	Obj() : v{ 0 }
	{
		std::cout << "Created\n";
	}

	Obj(const Obj& copy) : v{ copy.v } 
	{
		std::cout << "Copied\n";
	}

	Obj(Obj&& move) : v{ move.v }
	{
		std::cout << "Moved\n";
	}
	
	~Obj()
	{
		std::cout << "Destroyed\n";
	}
};

class FuncObj
{
	std::shared_ptr<Obj> state;

public:
	FuncObj(Obj* obj)
	{
		state = std::shared_ptr<Obj>(obj);
	}

	Obj& operator()(int value)
	{
		state->v += value;

		return *state.get();
	}
};

FuncObj MakeAClosureOldSchool()
{
	Obj* ptr = new Obj;

	FuncObj func(ptr);
	
	ptr->v = 5;

	return func;
}

void TestMakeAClosureOldSchool()
{
	auto xpto = MakeAClosureOldSchool();

	std::cout << xpto(10).v << std::endl;
	std::cout << xpto(20).v << std::endl;
}

int main(int argc, char* argv [])
{
	TestMakeAClosureOldSchool();

	return 0;
}