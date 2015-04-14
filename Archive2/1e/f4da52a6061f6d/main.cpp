#include <iostream>
#include <string>
#include <vector>

struct source_origin
{
    source_origin(const char* file, std::size_t line)
		: file(file)
		, line(line) {}

	const char* file;
	std::size_t line;
};

int main()
{
    source_origin a(__FILE__, __LINE);
    source_origin b;
    b = a;
}
