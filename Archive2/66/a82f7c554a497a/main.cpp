#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <deque>


void createTable(std::initializer_list<std::string> list)
{
    std::string res="Create table ";
	auto it = list.begin();
	res += *it;
	res += '(';
	int a = 0;
	for (++it; it != list.end(); ++it, ++a)
	{
		res += (*it+ ' ');
		if (a % 2)
			res += ',';
	}
	res.resize(res.size() - 1);
	res += ')';
	std::cout << res;
	
}
int main()
{
	createTable({"table1", "ID", "int", "Name", "string"});

}