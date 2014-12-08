namespace std
{
    template < typename > struct allocator ;
    template < typename, typename > struct vector ;
}

using int32_t = int ;
using float64_t = double ;

namespace shogun
{
    std::vector< int, std::allocator<int> > foo( std::vector< int, std::allocator<int> > v ) ;
    /** @brief MKLMulticlassOptimizationBase is a helper class for MKLMulticlass.
    *
    *   it is a virtual base class for MKLMulticlassGLPK and MKLMulticlassGradient which are instances of optimization
    *
    */
    class MKLMulticlassOptimizationBase // : public CSGObject
    {
        public:
            /** Class default Constructor
            *
            */
            MKLMulticlassOptimizationBase();
            /** Class default Destructor
            *
            */
            virtual ~MKLMulticlassOptimizationBase();

            /** initializes solver
            *
            * @param numkernels2 is the number of kernels
            *
            *
            */
            virtual void setup( const int32_t numkernels2 );

            /** adds a constraint to the LP arising in L1 MKL based on two parameters
            *
            * @param normw2 is the vector of \f$ \|w_k \|^2 \f$ for all kernels
            * @param sumofpositivealphas is a term depending on alphas, labels and
            * biases, see in the function float64_t getsumofsignfreealphas() from
            * MKLMulticlass.h, it depends on the formulation of the underlying GMNPSVM.
            *
            */
//virtual void addconstraint(const ::std::vector<float64_t> & normw2,
//  const float64_t sumofpositivealphas);
// virtual void addconstraint(const ::std::vector<float64_t> & normw2, const float64_t sumofpositivealphas);
            virtual void addconstraint( const ::std::vector< float64_t, std::allocator<float64_t> > & normw2, const float64_t sumofpositivealphas );

            /** computes MKL weights
            *
            * @param weights2 stores the new weights
            *
            */
//virtual void computeweights(std::vector<float64_t> & weights2);
// virtual void computeweights(std::vector<float64_t> & weights2);
            virtual void computeweights( std::vector< float64_t, std::allocator<float64_t> > & weights2 );
            /** @return object name */
            virtual const char* get_name() const { return "MKLMulticlassOptimizationBase"; }

            /** sets p-norm parameter for MKL
            *   @param norm the MKL norm
            */
            virtual void set_mkl_norm( float64_t norm );

        protected:


        protected:

    };
}

#include <vector>
template struct std::vector<float64_t> ;

int main()
{
}
