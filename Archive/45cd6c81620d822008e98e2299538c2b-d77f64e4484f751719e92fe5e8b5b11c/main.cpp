#include <stdio.h>
#include <utility>

struct S
{
    S() : data( new int ) 
	{ 
		printf("S constr\n"); 
	}

	S( S &&s )
	{
		printf("S move constr\n"); 
	 	data = s.data;
		s.data = 0;
	}


int *data;
};

struct I
{
	I()
	{}

	I( S &&ss ) : s( std::move(ss) )
	{
	}

S s;
};

I test()
{
	S s;
	*s.data = 100;

	printf(" data ptr %p\n", s.data);

	return I( static_cast<S &&>(s) );
}

int main()
{
I i = test();
//I j = i;		// a vot tak uze ne sdelaesh 

	printf(" data ptr %p\n", i.s.data);
	printf(" %d\n", *i.s.data );

return 0;
}