#include <cstdlib>


#define MYSIZE(v)    	(sizeof(v)/sizeof(v[0]))
#define MYEND(v)		(v + MYSIZE(v))

#define WANT_OUTPUT
#ifdef WANT_OUTPUT
#include <iostream>


#endif

int
cmpit(const void*	p1, const void*		p2)
{
	int**		i1p = (int **) p1;
	int**		i2p = (int **) p2;

	int		diff = -1;
	if (**i1p == **i2p) {
		diff = 0;
	} 
	if (**i1p > **i2p) {
		diff = 1;
	}

#ifdef WANT_OUTPUT
	std::cout << "cmpit(" << **i1p << ", " << **i2p << ")= "
			<< diff << "\n";
#endif
	return diff;
}

void
test() 
{	
	int *			source[7];
	int			sourceint[] = { 19,13,17,11,3,5,7 };

	// Make a vectored array.
	for (size_t	i = 0; i < MYSIZE(sourceint); i++) {
		source[i] = &sourceint[i];
	}

	//PRVECP(source);

	qsort((void *)source,
				MYSIZE(source), sizeof (int *), cmpit);

	//PRVECP(source);

}

int main()
{
    test();
}