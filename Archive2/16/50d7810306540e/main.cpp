#include <vector>

int main()
{
    float f = 8.75;
    int i = int (f);
    
    std::vector< double > vec_a (i);
    std::vector< double > vec_b (f);
    std::vector< double > vec_c ((int) f);
    std::vector< double > vec_d ((int (f)));
    std::vector< double > vec_e (int (f));
    
    // this is ok:
    vec_a[0] = 1.;
    // this is ok:
    vec_b[0] = 1.;
    // this is ok:
    vec_c[0] = 1.;
    // this is ok:
    vec_d[0] = 1.;
    // this is not:
    vec_e[0] = 1.;
    
	return 0;
}
