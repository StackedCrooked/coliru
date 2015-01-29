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

	Obj operator()(int value)
	{
		state->v += value;

		return *state.get();
	}
};

std::function<std::shared_ptr<Obj>(int)> MakeAClosureNotQuite()
{
	Obj ptr;	

	std::shared_ptr<Obj> shared = std::make_shared<Obj>(ptr);

	auto lambda = [=](int newValue) 
	{ 
		shared->v += newValue; return shared;
	};

	ptr.v = 5;

	return lambda;
}

std::function<Obj(int)> MakeAClosureBoldlyButWrong()
{
	Obj* ptr = new Obj;

	auto lambda = [=](int newValue)
	{
		std::shared_ptr<Obj> shared = std::shared_ptr<Obj>(ptr);

		shared->v += newValue; return *shared.get();
	};

	ptr->v = 5;

	return lambda;
}

FuncObj MakeAClosureOldSchool()
{
	Obj* ptr = new Obj;

	FuncObj func(ptr);
	
	ptr->v = 5;

	return func;
}

std::function<Obj(int)> MakeAPseudoClosure()
{
	Obj ptr;

	auto lambda = [=](int newValue) mutable { ptr.v += newValue; return ptr; };

	ptr.v = 5;

	return lambda;
}

std::shared_ptr<Obj> PlaysWithFire(std::function<std::shared_ptr<Obj>(int)> shared, int i)
{
	return shared(i);
}

Obj PlaysWithToy(std::function<Obj(int)> shared, int i)
{
	return shared(i);
}

void TestMakeAClosureNotQuite()
{
	auto xpto = MakeAClosureNotQuite();

	auto shared1 = PlaysWithFire(xpto, 10);
	auto shared2 = PlaysWithFire(xpto, 20);

	std::cout << shared1->v << std::endl;
	std::cout << shared2->v << std::endl;
}

void TestMakeAClosureEnhanced()
{
	auto xpto = MakeAClosureBoldlyButWrong();

	auto shared1 = PlaysWithToy(xpto, 10);
	auto shared2 = PlaysWithToy(xpto, 20);

	std::cout << shared1.v << std::endl;
	std::cout << shared2.v << std::endl;
}

void TestMakeAPseudoClosure()
{
	auto xpto = MakeAPseudoClosure();

	auto shared1 = PlaysWithToy(xpto, 10);
	auto shared2 = PlaysWithToy(xpto, 20);

	std::cout << shared1.v << std::endl;
	std::cout << shared2.v << std::endl;
}

void TestMakeAClosureOldSchool()
{
	auto xpto = MakeAClosureOldSchool();

	auto shared1 = PlaysWithToy(xpto, 10);
	auto shared2 = PlaysWithToy(xpto, 20);

	std::cout << shared1.v << std::endl;
	std::cout << shared2.v << std::endl;
}

int main(int argc, char* argv [])
{
	std::cout << "\nClosure wannable\n";

	TestMakeAClosureNotQuite();

	std::cout << "\nClosure snapshot\n";

	TestMakeAPseudoClosure();
	
	std::cout << "\nClosure trying to be like F#, C#, others\n";

	//TestMakeAClosureEnhanced();

	std::cout << "\nClosure like F#, C#, others\n";

	TestMakeAClosureOldSchool();

	return 0;
}