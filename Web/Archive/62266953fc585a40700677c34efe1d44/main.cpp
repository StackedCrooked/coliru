

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////DETAILS//////////////////////////////////////////////////

#include <ostream>
#include <typeinfo>

#define DEFINE_TYPE_NAME_DETAIL(type)  template<> const char* type_name<type>() { return #type; } 

#define DEFINE_TEMPLATE_NAME_DETAIL(template_type) \
template<typename ... Ts>\
struct template_name<template_type<Ts...>>\
{\
    static const char* name()\
    {\
		return #template_type;\
	}\
};

namespace snl
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////
		//compilation error message tags
		template<typename T> struct DEFINE_TYPE_NAME_;
		template<typename T> struct DEFINE_TEMPLATE_NAME_;
		
		///////////////////////////////////////////////////////////////////////////
		//primary template, specializations of which return displayable names!
		template<typename T>
		const char * type_name() {  DEFINE_TYPE_NAME_<T> DEFINE_TYPE_NAME_obj;  return "unknown_type"; }

		template<typename T>
		struct template_name
		{
			static const char* name()
			{
				DEFINE_TEMPLATE_NAME_<T> DEFINE_TEMPLATE_NAME_obj;
				return "unknown_template";
			}
		};		

		///////////////////////////////////////////////////////////////////////////
		//forward declaration
		template<typename T>
		struct single_type;

		///////////////////////////////////////////////////////////////////////////
		//iterate recursively
		template<typename ...Ts>
		struct iterate;

		template<>
		struct iterate<>    
		{
			static std::ostream & print(std::ostream & out) 
			{ 
				return out; 
			}
		};

		template<typename T>
		struct iterate<T>   
		{
			static std::ostream & print(std::ostream & out)
			{
				return single_type<T>::print(out);
			}
		};

		template<typename T, typename ...Ts>
		struct iterate<T, Ts...> 
		{
			static std::ostream & print(std::ostream & out) 
			{
				single_type<T>::print(out);
				out << ","; 
				iterate<Ts...>::print(out);
				return out;
			}
		};

		///////////////////////////////////////////////////////////////////
		//print single type
		template<typename T>
		struct single_type
		{
			static std::ostream& print(std::ostream & out)
			{
				return out << type_name<T>() ;
			}
		};

		//const qualified type
		template<typename T>
		struct single_type<T const>
		{
			static std::ostream& print(std::ostream & out)
			{
				return single_type<T>::print(out) << " const" ;
			}
		};
		
		//volatile qualified type
		template<typename T>
		struct single_type<T volatile>
		{
			static std::ostream& print(std::ostream & out)
			{
				return single_type<T>::print(out) << " volatile" ;
			}
		};

		//array type
		template<typename T, int N>
		struct single_type<T[N]>
		{
			static std::ostream& print(std::ostream & out)
			{
				return single_type<T>::print(out) << "[" << N << "]";
			}
		};

		//reference type
		template<typename T>
		struct single_type<T &>
		{
			static std::ostream& print(std::ostream & out)
			{
				return single_type<T>::print(out) << " &" ;
			}
		};

		//pointer type
		template<typename T>
		struct single_type<T*>
		{
			static std::ostream& print(std::ostream & out)
			{
				return single_type<T>::print(out) << "*";
			}
		};

		//template type [only type parameter(s)]
		template<template<typename...> class C, typename ...Ts>
		struct single_type<C<Ts...>>
		{
			static std::ostream& print(std::ostream & out)
			{
				out << template_name<C<Ts...>>::name() << "<" ;
				iterate<Ts...>::print(out);
				return out << ">";
			}
		};

		//function type
		template<typename R, typename ...Ts>
		struct single_type<R(Ts...)>
		{
			static std::ostream& print(std::ostream & out)
			{
				single_type<R>::print(out) << "(" ;
				return iterate<Ts...>::print(out) << ")" ;
			}
		};
		
		//function pointer type
		template<typename R, typename ...Ts>
		struct single_type<R (*) (Ts...)>
		{
			static std::ostream& print(std::ostream & out)
			{
				single_type<R>::print(out) << "(*)(" ;
				return iterate<Ts...>::print(out) << ")" ;
			}
		};
		
		//member function pointer type
		template<typename R, typename C, typename ...Ts>
		struct single_type<R (C::*) (Ts...)>
		{
			static std::ostream& print(std::ostream & out)
			{
				single_type<R>::print(out) << "(" ;
				single_type<C>::print(out) << "::*)(" ;
				return iterate<Ts...>::print(out) << ")" ;
			}
		};
	
		//const member function pointer type
		template<typename R, typename C, typename ...Ts>
		struct single_type<R (C::*) (Ts...) const>
		{
			static std::ostream& print(std::ostream & out)
			{
				return single_type<R(C::*)(Ts...)>::print(out) << " const" ;
			}
		};
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////API///////////////////////////////////////////////////////

#include <sstream>

#define DEFINE_TYPE_NAME(type)                           namespace snl { namespace detail { DEFINE_TYPE_NAME_DETAIL(type)              } }
#define DEFINE_TEMPLATE_NAME(template_type)              namespace snl { namespace detail { DEFINE_TEMPLATE_NAME_DETAIL(template_type) } }
#define DEFINE_TEMPLATE_NAME_NONTYPE(template_type, T)   namespace snl { namespace detail { DEFINE_TEMPLATE_NAME_DETAIL_NONTYPE(template_type, T) } }

namespace snl
{
    template<typename ...Ts>
	std::ostream& print(std::ostream & out)
	{
		return detail::iterate<Ts...>::print(out);
	}

	template<typename T>
	std::string name()
	{
		std::ostringstream out;
		print<T>(out);
		return out.str();
	}
}

DEFINE_TEMPLATE_NAME(std::char_traits)
DEFINE_TEMPLATE_NAME(std::basic_string)
DEFINE_TEMPLATE_NAME(std::allocator)

DEFINE_TYPE_NAME(void)
DEFINE_TYPE_NAME(bool)
DEFINE_TYPE_NAME(char)
DEFINE_TYPE_NAME(wchar_t)
DEFINE_TYPE_NAME(short)
DEFINE_TYPE_NAME(int)
DEFINE_TYPE_NAME(long)
DEFINE_TYPE_NAME(unsigned char)
DEFINE_TYPE_NAME(unsigned short)
DEFINE_TYPE_NAME(unsigned int)
DEFINE_TYPE_NAME(unsigned long)
DEFINE_TYPE_NAME(signed char)
DEFINE_TYPE_NAME(float)
DEFINE_TYPE_NAME(double)

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////TEST CODE////////////////////////////////////////////

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <list>

struct A { typedef int (A::*pf)(int,int); };

template<typename T>
struct B { typedef T (B::*pf)(T*, T**); };

template<typename T>
struct C {};

DEFINE_TYPE_NAME(A)
DEFINE_TEMPLATE_NAME(B)
DEFINE_TEMPLATE_NAME(C)
DEFINE_TEMPLATE_NAME(std::vector)
DEFINE_TEMPLATE_NAME(std::list)
DEFINE_TEMPLATE_NAME(std::_List_const_iterator)

typedef int funtype(double, A);

int main()
{
    try 
	{
		snl::print<B<int>, decltype(&std::list<int>::cbegin)>(std::cout) << "\n";
		snl::print<funtype, funtype *,  B<A>::pf, A::pf, int[100], char[20][30][20] >(std::cout) << "\n";
		snl::print<int,short &,char const * const & ,wchar_t*[10]>(std::cout) << "\n";
		
		std::cout << snl::name<void>() << std::endl;
		std::cout << snl::name<A>() << std::endl;
		std::cout << snl::name<A const>() << std::endl;
		std::cout << snl::name<A *>() << std::endl;
		std::cout << snl::name<A const*>() << std::endl;
		std::cout << snl::name<A const* volatile>() << std::endl;
		std::cout << snl::name<A * const>() << std::endl;
		std::cout << snl::name<A volatile * const>() << std::endl;
		std::cout << snl::name<A const * const>() << std::endl;
		std::cout << snl::name<std::string * const>() << std::endl;
		std::cout << snl::name<C<B<A**>***>****>() << std::endl;
		
		std::cout <<"\n\n";
		snl::print<std::list<std::vector<C<B<A>>>>>(std::cout);
		
		std::cout <<"\n\n";
		snl::print<std::char_traits<char>>(std::cout);

		std::cout <<"\n\n";
		snl::print<std::wstring, std::vector<std::string>>(std::cout);

		std::cout <<"\n\n";
		snl::print<std::char_traits<char>, std::basic_string<char, std::char_traits<char>, std::allocator<char>>>(std::cout);
	}	
	catch(std::exception const & e)
	{
		std::cout << "exception message = " << e.what() << std::endl;
	}
}
