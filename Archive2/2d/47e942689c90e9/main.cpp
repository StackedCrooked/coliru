#include <vector>
#include <complex>
using namespace std;

template <class T, class U, class V>
class PP_FIR
{
public:
    PP_FIR() {};
    PP_FIR(const std::vector< std::vector<T> > & coef, const size_t n_phase, const U state = 0, const U sum = 0) {}

    void Update(const U & , const std::vector<size_t> &, std::vector<V> &) {}
private:
};

int main()
{
    vector< PP_FIR< double,complex<double>,complex<double> > > myFIR;
    vector< vector<double> > myCoef;
    vector< size_t > myPhase;
    complex<double> state = complex<double>(0.0,0.0);
    complex<double> sum = complex<double>(0.0,0.0);
    complex<double> sample_in = complex<double>(5.0,0.0);
    vector< complex<double> > sample_out(2, complex<double>(0.0,0.0));
    size_t phase = 4;
    
    myCoef.resize(4, vector<double>(20,1.0));
    myPhase.push_back(1);
    myPhase.push_back(2);
    
    myFIR.resize(4,PP_FIR< double,complex<double>,complex<double> >(myCoef, phase, state, sum));
    
    for ( int k=0; k<4; ++k ) {
        myFIR[k].Update(sample_in, myPhase, sample_out);
    }
}