#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
    auto generic_lambda = [](auto... param) {
		std::ostringstream stream;
		using List = int[];
		(void)List{ 0, ((void)(stream << param), 0) ... };
		return stream.str();
	};
	std::cout << generic_lambda(1, 2, 3, "qwe");
}