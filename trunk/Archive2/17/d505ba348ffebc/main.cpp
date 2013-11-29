#include <cstdlib>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

using namespace std;



static std::map<std::string, int> counters_v;
static bool                       counting = false;


static void count(const char *func)
{
    if (counting) {
		counters_v[func]++;
	}
}


class Example
{
    public:
	Example()
	{
		count(__PRETTY_FUNCTION__);
	}

	~Example()
	{
		count(__PRETTY_FUNCTION__);
	}

	// Copy constructor
	Example(const Example& other)
	{
		count(__PRETTY_FUNCTION__);
	}
};


void push_test(const Example& ex)
{

	std::vector<Example> vec;

	printf("vec.size()=%lu  vec.capacity()=%lu\n", (unsigned long)vec.size(), (unsigned long)vec.capacity());

	for (int i = 0; i < 5; ++i) {
		vec.push_back(ex);
		printf("vec.push_back(ex) -> vec.size()=%lu  vec.capacity()=%lu\n",
		       (unsigned long)vec.size(), (unsigned long)vec.capacity());
	}
}


int main()
{
	Example ex;

	counting = true;
	push_test(ex);
	counting = false;

	printf("\nCounters:\n");
	for (const auto& p : counters_v) {
		printf("%s: %d\n", p.first.c_str(), p.second);
	}

	return EXIT_SUCCESS;
}
