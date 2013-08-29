// CompilerVersion=VS2012CTP

#include <utility>
#include <string>
#include <initializer_list>
#include <vector>
#include <list>
#include <iostream>
#include <utility>

struct Ctp {
    Ctp(int count, const char* greeting)
		: m_vec(count, greeting)
	{
	}

	Ctp(Ctp& other)
	{
		m_vec = other.m_vec;
	}
	
	// initializer_list
	Ctp(std::initializer_list<const char*> list):
		Ctp(1, "Hello " ) // delegating constructors
	{
		m_vec.insert(m_vec.end(), list.begin(), list.end());
	}

	explicit operator std::string() const // explicit conversion operator
	{
		std::string ss; 
		for(const auto& s : m_vec) // range-based for
		{
			ss += s;
		}
		return ss;
	};

	template<typename T = std::string> // default argument for function templates
	T to_string() const
	{
		T ss;
		for(const auto& s : m_vec)
		{
			ss.insert(ss.end(), s.begin(), s.end());
		}
		return ss;
	}

	Ctp(Ctp&& other)
	{
		m_vec = std::move(other.m_vec);
	}

	Ctp& operator=(Ctp&& other)
	{
		m_vec = std::move(other.m_vec);
        return *this;
	}

private:
	std::vector<std::string> m_vec;
};

template<typename... T> // variadic template
Ctp make_ctp(T... t)
{
	return Ctp( {t...} );
}

int main()
{
	Ctp ctp1 = { 3, R"(He"l"lo )" }; // uniform initialization; raw string literals
	Ctp ctp2 = { "sunshine ", "and ", "the ", "rain" }; // initializer list
	Ctp ctp3 = { "constructor" };
	Ctp ctp4 = make_ctp("variadic ", "template"); 

	auto msg1 = ctp4.to_string(); // calling with default arguments for function template
	auto msg2 = ctp4.to_string<std::vector<char>>();

	// error: explicit conversion prevents the line below from compiling
	//std::string msg3 = ctp1;
	std::string msg4 = static_cast<std::string>(ctp1); // explicit conversion

	std::cout <<
		msg1 << std::endl << 
		static_cast<std::string>(ctp2) << std::endl << 
		static_cast<std::string>(ctp3) << std::endl <<
		static_cast<std::string>(ctp4) << std::endl;
}
