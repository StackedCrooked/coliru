#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

/**
 * Defines a class and template specialization, for a variable, needed for use with the GET_PRIVATE hook below
 *
 * @param InClass    	The class being accessed (not a string, just the class, i.e. FStackTracker)
 * @param VarName		Name of the variable being accessed (again, not a string)
 * @param VarType		The type of the variable being accessed
 */
#define IMPLEMENT_GET_PRIVATE_VAR(InClass, VarName, VarType) \
	struct InClass##VarName##Accessor \
	{ \
		typedef VarType InClass::*Member; \
		\
		friend Member GetPrivate(InClass##VarName##Accessor); \
	}; \
	\
	template struct AccessPrivate<InClass##VarName##Accessor, &InClass::VarName>;
    
/**
 * A macro for tidying up accessing of private members, through the above code
 *
 * @param InClass    	The class being accessed (not a string, just the class, i.e. FStackTracker)
 * @param InObj			Pointer to an instance of the specified class
 * @param MemberName	Name of the member being accessed (again, not a string)
 * @return				The value of the member 
 */
#define GET_PRIVATE(InClass, InObj, MemberName) (*InObj).*GetPrivate(InClass##MemberName##Accessor())

class Blah
{
private:
    class InnerClass
    {
    public:
        
        int A;
    };
    
    InnerClass Inner;
};

Blah Blah;

// Works in most cases of wanting to access private variables, but not in this case
IMPLEMENT_GET_PRIVATE_VAR(Blah, Inner, Blah::InnerClass);

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    int& ARef = GET_PRIVATE(Blah, Blah, Inner).A;
}
