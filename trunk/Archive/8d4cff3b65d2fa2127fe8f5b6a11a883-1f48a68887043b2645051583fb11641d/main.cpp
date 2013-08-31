#include<iostream>

class bar
    {
	public:
		template<typename T>
		void foo(T t);

	//	template<>
	//	void foo<int>(int t)
	};


template<typename T>
void bar::foo(T t)
{
   std::cout << t;
}

//What the hell is this????? Isn't it missing <> after template???
template
void bar::foo<int>(int t);

int main(int argc, char* argv[])
{
 double f = 0.5f;
 bar b;
 b.foo<double> (f);
	return 0;
}
