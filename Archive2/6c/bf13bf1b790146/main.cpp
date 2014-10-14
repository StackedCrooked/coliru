#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <deque>


enum class Types{id,Int,string};
namespace details
{
    std::vector<std::string> names,types;

}
std::string toStr(Types name)
{
	std::string out;
	switch (name)
	{
	case Types::id:
		out += "ID";
		break;

	case Types::Int:
		out += "INT";
		break;
	case Types::string:
		out += "TEXT";
		break;
	}
	return out;
}
template <class...Args>
void createTable(const std::string& name,const Args&... args)
{	
	details::names.push_back(name);
	createTable(args...);
}
template <class...Args>
void createTable(Types name, const Args&... args)
{
	details::types.push_back(toStr(name));
	createTable(args...);
}

void createTable()
{
	std::string res = "Create table ";
	res += details::names[0];
	res += '(';
	auto it2 = details::types.begin();
	for (auto it = details::names.begin() + 1;
		it != details::names.end();++it,++it2)
	{
		res += (*it + ' '+ *it2 +',');
	}
	res[res.size()-1]= ')';
	std::cout << res;
	details::names.clear();
	details::types.clear();
}
int main()
{
	createTable("table1", "id", Types::Int, "Name", Types::string);

}

