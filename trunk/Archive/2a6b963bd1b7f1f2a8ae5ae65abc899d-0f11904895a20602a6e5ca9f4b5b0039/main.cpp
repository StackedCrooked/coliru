#include <complex>

template<class T>
struct matrix {
    
    matrix() {}
    
    matrix(int,int){}
    
    template<class U>
    matrix(const matrix<U>&) {}
    
    template<class U>
    matrix operator*(const matrix<U>&) const {return {};}
    
    int size(int) const {return 0;}
    
    T operator()(int,int) const {return {};}
};

template<class T, class U>
auto operator*(const T& a, const matrix<U>& A) -> matrix<decltype(a*A(0,0))>
{
    using result_type = decltype(a*A(0,0));
    matrix<result_type> B(A.size(1),A.size(2));
    for(int ii = 0; ii < B.size(1); ii++)
    {
        for(int jj = 0; jj < B.size(2); jj++)
        {
            B(ii,jj) = a*A(ii,jj);
        }
    }
    return B;
}

int main() {
    std::complex<double> a1;
    matrix<std::complex<double> > A1;
    double a2;
    matrix<std::complex<double> > A2;
    
    /* ... */
    
    matrix<std::complex<double> > B1 = a1*A1; // Compiler error
    matrix<std::complex<double> > B2 = a2*A2; // Compiles and runs fine.
}