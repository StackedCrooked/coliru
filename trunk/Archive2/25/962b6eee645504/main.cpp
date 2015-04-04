#include <iostream>
#include <string>
#include <sstream>
#include "lua.hpp"
#include "sol.hpp"

#include "Flexiglass.hpp"
//Basically std::list + flgl::any

//Credit to sehe, user of Stack Overflow
//Code has been modified from example

#include <memory>
#include <stdexcept>

namespace flgl
{
    
class any
{
public:
	//Keep the default constructor
    any() = default;
	
	//Templated initialization
    template <typename T>
	any(const T& v)
	: data(new storage<T>(v))
	{ }
	
	//Copy constructor, move a clone of other data or keep a nullptr if empty
    any(const any& other)
	: data(other.data ? std::move(other.data->clone()) : nullptr)
	{}

	//Swap
    void swap(any& other)
	{
		data.swap(other.data);
	}
	
	//Global wrapper for swap method

	
	//Assignment
    any& operator=(any other)
	{
		swap(other);
		return *this;
	}

    //Move semantics to be implemented later
private:

	//Virtual interface for storage
    struct storage_base { 
        virtual std::unique_ptr<storage_base> clone() = 0;
        virtual ~storage_base() = default; 
    };
	
	//Templated storage unit
    template <typename T>
    struct storage : storage_base {
		//The actual value
        T value;
		
		//Value constructor
        explicit storage(const T& v)
		: value(v)
		{}
		
		//Return a clone of internals
        std::unique_ptr<storage_base> clone()
		{
			return std::unique_ptr<storage_base>(new storage<T>(value));
		}
		
    };
	
	//Private members
    std::unique_ptr<storage_base> data;
	
	//friends
    template<typename T>
	friend T& any_cast(any&);
	
    template<typename T>
	friend T const& any_cast(const any&);
	
	friend void swap(flgl::any& a, flgl::any& b)
	{
		a.swap(b);
	}
};

template <typename T>
T& any_cast(any& a)
{ 
    if (auto p = dynamic_cast<any::storage<T>*>(a.data.get()))
        return p->value;
    else
        throw std::bad_cast();
}

template <typename T>
T const& any_cast(const any& a)
{ 
    if (auto p = dynamic_cast<any::storage<T> const*>(a.data.get()))
        return p->value;
    else
        throw std::bad_cast();
	
	
}

}

int main()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	lua.open_libraries(sol::lib::io);
	
	//Set boost::any object to a std::string value and pass it to Lua.
	flgl::any obj(std::string("hello"));
	
	//This syntax should work here. I did a test case with a templated function.
	lua.set_function("unpack", flgl::unpack<std::string>);
	lua.set("b", obj);
	
	lua.new_usertype<flgl::Event, std::string, std::string>("Event", "push_data", flgl::Event::push_data<std::string>);
	
	//sol::usertype<boost::any> utype("boost_any", ctors);
	//lua.set_usertype(utype);
	
	//Contents:
	//print('Hello World!')
	//unpack(b)
	lua.open_file("test.lua");
	
	flgl::Event lua_e = lua.get<flgl::Event>("e");
	flgl::data_list lua_e_data_list = lua_e.get_data();
	
	for (auto it : lua_e_data_list)
	{
		std::string str = flgl::unpack<std::string>(it);
	}
	
	return 0;
}