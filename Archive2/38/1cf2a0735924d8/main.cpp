#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

using namespace boost::numeric::ublas;

namespace boost { namespace numeric { namespace ublas {
    template<class V>
    inline
    void swap (boost::numeric::ublas::index_pair<V> i1, boost::numeric::ublas::index_pair<V> i2) {
        i1.swap (i2);
    }
    template<class M>
    inline
    void swap (boost::numeric::ublas::index_triple<M> i1, boost::numeric::ublas::index_triple<M> i2) {
        i1.swap (i2);
    }
    
    template<class C, class IC>
    inline
    void iter_swap (boost::numeric::ublas::indexed_iterator<C, IC> it1,
                    boost::numeric::ublas::indexed_iterator<C, IC> it2) {
        swap (*it1, *it2);
    }
}}}

int main(int argc, char** argv) {
  coordinate_matrix<int> m1(100, 100, 100);

  for (int i = 0; i < 100; i++)
    m1.insert_element(i,i,i);

  compressed_matrix<int> m2(m1, 100);
}
