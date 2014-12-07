#include <iomanip>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstdlib>
#include <type_traits>

const int n = 1000;
double a[n][n], b[n][n], c[n][n];

std::shared_ptr<double> s[n*n];


template<typename T, bool b> 
struct Foo { static const int id = 0; };

template<typename T>
struct Foo<T, (typename std::enable_if<T::has, bool>::type)true> { static const int id = 1; };

template<typename T>
struct Foo<T, (typename std::enable_if<T::has, bool>::type)false> { static const int id = 2; };

template<typename T>
struct Foo<T, (typename std::enable_if<!T::has, bool>::type)true> { static const int id = 3; };

template<typename T>
struct Foo<T, typename std::enable_if<!T::has, bool>::type(false)> { static const int id = 4; };

struct S0 {};

struct S1 { static const bool has=true; };

struct S2 { static const bool has=false; };

#define DUMP(x) std::cout << #x << ":" << (x) << std::endl;

// compute c=a*transpose(b); a=c; roughly 1 billion floating point operations
void fp_operations_1G()
{
    for (int i=0; i<n; i++)    
        for (int j=0; j<n; j++) {
            double sum = 0;
            for (int k=0; k<n; k++)
                sum += a[i][k]*b[j][k];
            c[i][j] = sum;
        }
}

// rotate a vector of shared_ptr. 1 million operations (shared_ptr counter inc and dec)
void shared_ptr_operation_1M()
{
    for (int k=0; k<n; k++) {
        std::shared_ptr<double> last = s[n-1];
        for (int i=1; i<n; i++) 
            s[i]=s[i-1];
        s[0] = last;
    }
}

// returns the fractional number of times fun() can be called in one second.
double run(void (*fun)())
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    int count = 0;
    while (true) {
        fun();
        count++;

        double millis = duration_cast<milliseconds>(high_resolution_clock::now()-start).count();

        if (millis > 4000) 
            return count*1000.0/millis;
    }
}

void setup()
{
    srand(0);
    for (int i=0; i<n; i++)    
        for (int j=0; j<n; j++) {
            a[i][j] = 2.0*std::rand()/RAND_MAX-1;
            b[i][j] = 2.0*std::rand()/RAND_MAX-1;
        }
    
    for (int i=0; i<n; i++) 
        s[i].reset(new double(std::rand()));
}

int main()
{
    DUMP((Foo<S0,true>::id));
    DUMP((Foo<S0,false>::id));
    DUMP((Foo<S1,true>::id));
    DUMP((Foo<S1,false>::id));
    DUMP((Foo<S2,true>::id));
    DUMP((Foo<S2,false>::id));

    std::cout << "setting up ... " << std::flush;
    setup();
    std::cout << "done." << std::endl;

    std::cout << "testing matrix multiplication... " << std::flush;
    double fp_ops = run(fp_operations_1G);
    std::cout << "done." << std::endl;

    std::cout << std::fixed << std::setprecision(0);
    std::cout << 1e9*fp_ops << " floating point multiplications per second." << std::endl;

    std::cout << "testing shared_ptr... " << std::flush;
    double sptr_ops = run(shared_ptr_operation_1M);
    std::cout << "done." << std::endl;
    std::cout << 1e6*sptr_ops << " shared_ptr attach/detach per second." << std::endl;

    std::cout << std::setprecision(1) << (1e3*fp_ops/sptr_ops) 
        << " floating point multiplications per each shared_ptr attach/detach." << std::endl; 

}
