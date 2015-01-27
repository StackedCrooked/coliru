#include <initializer_list>
#include <cstdio>

template<typename T>
class II
{
public:
    II(std::initializer_list<int> l1)
	{
		printf("one list\n");
	}
	II(std::initializer_list<int> l1, std::initializer_list<int> l2)
	{
      	//static_assert(sizeof(T) == 0, "");
		printf("two lists\n");
	}
};

int main()
{
	II<int> i1{ std::initializer_list<int>{ 1 },{ 2 } };
	II<int> i2{ { { 1 } }, { { 2 } } };

	return 0;
}
