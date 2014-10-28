#include <iostream>
#include <math.h>
#include <vector>

int main()
{
    double f = 8.75;
    int i = int (f);
    std::vector< double > vec_a (i);
    std::vector< double > vec_b (int (f));
    
    // this is ok:
    vec_a[0] = 1.;
    // this is not:
    vec_b[0] = 1.;
    
	return 0;
}
