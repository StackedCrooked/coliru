#include <iostream>
#include <string>

struct catcher {
    catcher(const char* name) : name_(name) {}
    const char* name_;
};

struct string_literal {

	template<unsigned LEN>
    string_literal(const char(&p)[LEN]) : start_(p), length_(LEN - 1) { }
	const char* start_;
    unsigned length_;
};

int main()
{
	catcher filename(__FILE__);

#if 1
	const char p[] = filename.name_;
#else    
  	const char p[] = __FILE__;
#endif      
	string_literal lit(p);

	std::cout << std::string(lit.start_, lit.length_) 
		<< std::endl;

	return 0;
}
