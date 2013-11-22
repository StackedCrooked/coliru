#include <iomanip>
#include <iostream>
#include <set>
#include <type_traits>


template<typename T>
bool areAllUnique(std::initializer_list<T> init){
    std::set<T> check{init};
	return check.size() == init.size();
}

int main()
{
	using namespace std;
#define DBG(x) { cout << setw(30) << left << #x << boolalpha << x << endl; }

	DBG(areAllUnique({1,2,3,4,5}));
	DBG(areAllUnique({1,2,3,4,4}));
	DBG(areAllUnique({1,2,3}));
	DBG(areAllUnique({1,1,1}));
}
