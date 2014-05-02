#include <string>
#include <vector>
#include <iostream>


template <typename String, template<class> class Allocator>
class basic_data_object
{
  template<typename T>
  using array_container = std::vector<T, Allocator<T>>;
};

template <typename String, template<class> class Allocator, typename T>
struct get_data_object_value
{
    void foo() { std::cout << "general" << std::endl; }
};

template <typename String, template<class> class Allocator, typename T>
struct get_data_object_value
<String, Allocator,
typename basic_data_object<String, Allocator>::template array_container<T>>
{
	void foo() { std::cout << "does not work" << std::endl; }
};


template<typename String, template<class> class Allocator, typename T>
using a_type = basic_data_object<String,Allocator>::array_container<T>;

template <typename String, template<class> class Allocator, typename T>
struct get_data_object_value<String, Allocator, a_type<String,Allocator,T>>
{
	void foo() { std::cout << "it works!" << std::endl; }
};


int main()
{

  get_data_object_value<std::string,std::allocator,std::vector<int>> obj;
  obj.foo();
}