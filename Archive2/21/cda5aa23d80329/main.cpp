#include <ctype.h>
#include <string>
#include <vector>
#include <iostream>

bool is_double(std::string const &input) { 
    size_t pos = 0;
	while (input[pos] == ' ')
		++pos;
	if (input[pos] == '-')
	    ++pos;
	if (input[pos] == ' ')
		++pos;
	while (isdigit(input[pos]))
		++pos;
	if (input[pos] == '.')
		++pos;
	while (isdigit(input[pos]))
		++pos;
	if (input[pos] == 'e' || input[pos] == 'E') {
		++pos;
		while (isdigit(input[pos]))
			++pos;
	}
	return input[pos] == '\0';
}

struct test { 
	std::string input;
	bool result;
};

int main(){ 
	std::vector<test> test_inputs{
		{ "1", true },
		{ "-1", true },
		{ "1.2", true },
		{ "-1.3", true },
		{ "1.", true },
		{ ".3", true },
		{ "-.4", true },
		{ "1e3", true },
		{ "1.2e3", true },
		{ "f", false },
		{ "-f", false },
		{ "e", false }
	};

	for (auto t : test_inputs)
		if (is_double(t.input) == t.result) 
			std::cout << "Test of : " << t.input << " passed\n";
		
		else
			std::cout << "Test of : " << t.input << " failed\n";
}		

