#include <new>
//Boost for sparse and cstdint
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/cstdint.hpp>

int main(){

    boost::numeric::ublas::compressed_vector<boost::int_fast8_t> *p = new boost::numeric::ublas::compressed_vector<boost::int_fast8_t>[100];
    boost::numeric::ublas::compressed_vector<boost::int_fast8_t> t (12,2);

    p[0] = t;

    for(boost::int_fast8_t i=0; i < t.size();i++)
    {
        p[0](i) = i;
    }

    std::cout << p[0] << std::endl;
}
