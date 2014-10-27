#include <iostream>
#include <string>
#include <map>
#include <typeindex>

#include <boost/any.hpp>

class heterogenous_map :
    std::map<std::type_index, boost::any>
{
public:

	template <typename T>
	void add(T&& value)
	{
		emplace(typeid(typename std::remove_reference<T>::type), std::forward<T>(value));
	}

	template <typename T>
	T& get(std::type_index const& ti) { return *boost::any_cast<T>(&at(ti)); }
	template <typename T>
	T const& get() const { return *boost::any_cast<T>(&at(typeid(T))); }
};

int main()
{
	heterogenous_map map;
	map.add(6584);
	map.add<std::string>("Hi!");

	std::cout << "My favourite integer: " << map.get<int>() << '\n';
	std::cout << "My favourite string : " << map.get<std::string>() << std::endl;
}
