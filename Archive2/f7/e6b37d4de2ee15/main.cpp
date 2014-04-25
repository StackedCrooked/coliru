#include <cstdio>
#include <ctime>
#include "boost/pool/pool.hpp"

struct Letter{
    float a, b, c;
	int *p;
};

class Label
{
public:
	Label() : m_myArray(NULL), string_length(1), last_size(0){}

	void set_size(size_t n)
	{
		last_size = string_length;
		string_length = n;
	}
	void ParseText()
	{
		delete[] m_myArray;
		m_myArray = new Letter[string_length];
	}

	void ParseText_pool();

private:
	Letter* m_myArray;
	size_t string_length;
	size_t last_size;
};

boost::pool<> p(sizeof(Letter));

void Label::ParseText_pool()
{
	if(m_myArray)
		p.ordered_free(m_myArray, last_size);
	m_myArray = (Letter*)p.ordered_malloc(string_length);
}

int main()
{
	Label l;

	float startTime = (float)clock()/CLOCKS_PER_SEC;

	for(int i = 1; i < 1000000; ++i)
	{
		l.set_size(i%100 + 1);
		l.ParseText();
	}

	float endTime = (float)clock()/CLOCKS_PER_SEC;

	printf("without pool, time: %f\n", endTime - startTime);

	Label l2;
	startTime = (float)clock()/CLOCKS_PER_SEC;

	for(int i = 1; i < 1000000; ++i)
	{
		l.set_size(i%100 + 1);
		l2.ParseText_pool();
	}

	endTime = (float)clock()/CLOCKS_PER_SEC;

	printf("with pool, time: %f\n", endTime - startTime);
};