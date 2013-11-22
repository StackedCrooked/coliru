#include <type_traits>
#include <iostream>

class my_char
    {
	public:
	    my_char() = default;
        my_char(const my_char&) = default;
        
	    my_char(const char x) : val(x) {};
	    bool operator < (const my_char & x) const
	    {
		if(val == '/')
		    if(x.val == '/')
			return false;
		    else
			return true;
		else
		    if(x.val == '/')
			return false;
		    else
			return val < x.val;
	    };

	    operator char() const
	    {
		return val;
	    };

	private:
	    char val;
	};
    
int main() {
    std::cout << std::is_pod<my_char>::value;
}