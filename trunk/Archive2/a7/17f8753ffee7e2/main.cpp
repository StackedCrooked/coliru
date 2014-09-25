#include <iostream>
#include <map>
#include <string>

unsigned foo() { return 12345u; }

int main() {
    
	std::map<std::string, std::string> m;
	
	// gcc implicitly converting unsigned to string???
	m["abc"] = 12345u;
	m["def"] = foo();
	m["ghi"] = std::to_string(foo());

	for(auto p : m)
	{
		std::cout << p.first << " = " << p.second << "\n";
	}
	
	return 0;
}
