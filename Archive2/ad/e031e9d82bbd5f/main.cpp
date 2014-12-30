#include <boost/numeric/ublas/vector.hpp>
#include <boost/mpi/collectives/gather.hpp>
#include <iostream>

template <typename T> struct Column { 
    T v; 
    Column(T const& v) : v(v) {}
    friend std::ostream& operator<<(std::ostream& os, Column<T> const& cv) {
        return os << cv.v;
    }
};

int main() {
    boost::mpi::communicator boost_comm;
    typedef boost::numeric::ublas::vector<double> ublasv;
    
    ublasv distributed_boost_vector, all_boost_vector;
    boost::mpi::gather(boost_comm, distributed_boost_vector, &all_boost_vector, 0);

    std::vector<ublasv> out_values;
    boost::mpi::gather(boost_comm, distributed_boost_vector, out_values, 0);
}
