#include <ctype.h>
#include <string>
#include <vector>
#include <iostream>

bool is_double(std::string const &input) { 
    size_t pos = 0;
    bool found_digit = false;
	while (input[pos] == ' ')       // Eat leading spaces
		++pos;
	if (input[pos] == '-')          // Then check for a possible leading minus-sign
	    ++pos;
	if (input[pos] == ' ')          // Then more spaces
		++pos;
	while (isdigit(input[pos])) {   // Then some digits. Keep track of whether we found at least one
        found_digit = true;
		++pos;
	}
	if (input[pos] == '.')          // then a decimal point
		++pos;
	while (isdigit(input[pos])) {   // then more digits (again track whether we found at least one)
        found_digit = true;
		++pos;
	}
	if (input[pos] == 'e' || input[pos] == 'E') {   // the an optional `e`.
		++pos;
        if (input[pos] == '-')      // followed by an optional minus sign
            ++pos;
        if (!isdigit(input[pos]))   // if the `e` was present, it must be followed by at least one digit
            return false;
		while (isdigit(input[pos])) {
			++pos;
		}
	}
	return found_digit && input[pos] == '\0';
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
        { "-12.34e56", true },
        { "-1.23e-78", true },
		{ "f", false },
		{ "-f", false },
		{ "e", false },
        { ".e", false },
        { "e1", false }        
	};

	for (auto t : test_inputs)
		if (is_double(t.input) == t.result) 
			std::cout << "Test of : " << t.input << " passed\n";
		
		else
			std::cout << "Test of : " << t.input << " failed\n";
}		

