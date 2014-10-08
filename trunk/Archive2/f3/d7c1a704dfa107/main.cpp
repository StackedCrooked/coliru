#include <iostream>
#include <list>

struct Base {};
// Thanks for this to Piotr S.
struct A : Base { A(){std::cout<<"A";} };
struct B : Base { B(){std::cout<<"B";} };
struct C : Base { C(){std::cout<<"C";} };
struct D : Base { D(){std::cout<<"D";} };
struct E : Base { E(){std::cout<<"E";} };
struct F : Base { F(){std::cout<<"F";} };

template <int KEY, typename... RANGE> struct Map {};

template <typename... T> struct Data {};

using Database = Data<Map<0, A,B,C>, Map<1, D,E,F>>;

// There is no need to take the length here, btw.
template <int, typename... Args>
void insertInMenu (std::list<Base*>& menu)
{
    // Non-recursive push_backs:
	std::initializer_list<int>{ (menu.push_back(new Args), 0)... };
}

template <int, typename> struct InsertEnv;

template <int key, int otherKey, typename... Args, typename... Rest>
struct InsertEnv<key, Data<Map<otherKey, Args...>, Rest...>> :
	InsertEnv<key, Data<Rest...>> {};

template <int key, typename... Args, typename... Rest>
struct InsertEnv<key, Data<Map<key, Args...>, Rest...>>
{
	void operator()(std::list<Base*>& menu)
	{
		// Non-recursive push_backs:
		insertInMenu<key, Args...> (menu);
	}

	std::list<Base*> operator()()
	{
		return {new Args...};
	}
};

template <int N>
void addToMenu (std::list<Base*>& menu)
{
	InsertEnv<N, Database>()(menu);
}

template <int N>
std::list<Base*> menu()
{
	return InsertEnv<N, Database>()();
}

int main()
{
    std::list<Base*> m1 = menu<0>();
    std::cout << ", m1.size() = " << m1.size() << std::endl;
    addToMenu<1>(m1);
    std::cout << ", m1.size() = " << m1.size() << std::endl;
}
