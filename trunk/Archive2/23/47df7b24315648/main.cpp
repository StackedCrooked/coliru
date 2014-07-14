#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void t1(int argc, char *argv[])
{
    const std::string kFlashLimintArgName = "-myparam";

	char ** search_begin = argv + 1;
	char ** search_end = argv + (argc - 1);

	char** flash_limit = std::find(search_begin, search_end, kFlashLimintArgName);

	if (flash_limit != search_end)
	{
		std::cout << "Found!"<<endl;
	}
	else
	{
		std::cout << "Not found!"<<endl;
	}
}

void t2(int argc, char *argv[])
{
	char ** search_begin = argv + 1;
	char ** search_end = argv + (argc - 1);

	char** flash_limit = std::find(search_begin, search_end, "-myparam");

	if (flash_limit != search_end)
	{
		std::cout<<"Found!"<<endl;
	}
	else
	{
		std::cout << "Not found!"<<endl;
	}
}

void t3(int argc, char *argv[])
{
    char ** search_begin = argv + 1;
	char ** search_end = argv + (argc - 1);
    char **it = search_begin;
	for (it; it != search_end; it++)
    {
        cout<<*it<<endl;
    }
}

int main(int argc, char *argv[]) 
{
	t1(argc,argv);
	t2(argc,argv);
    t3(argc,argv);
}