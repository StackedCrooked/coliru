#include <stddef.h>
#include <limits>

template<class OPTIMIZER, class DenseMatrix>
class TransportationSolver
{
public:
    typedef float floatType;
    static const floatType floatTypeEps;
    static const size_t defaultMaxIterationNumber;
	static const size_t MAXSIZE_T;
};

template<class OPTIMIZER,class DenseMatrix>
const typename TransportationSolver<OPTIMIZER, DenseMatrix >::floatType TransportationSolver<OPTIMIZER, DenseMatrix >::floatTypeEps = std::numeric_limits<typename TransportationSolver<OPTIMIZER, DenseMatrix >::floatType >::epsilon();

template<class OPTIMIZER,class DenseMatrix>
const size_t TransportationSolver<OPTIMIZER, DenseMatrix >::MAXSIZE_T = std::numeric_limits<std::size_t >::max();

template<class OPTIMIZER,class DenseMatrix>
const size_t TransportationSolver<OPTIMIZER, DenseMatrix >::defaultMaxIterationNumber = 100;

int main() {}