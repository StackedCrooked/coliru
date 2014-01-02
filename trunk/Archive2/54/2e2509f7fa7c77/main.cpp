#include <cstdlib>
#include <memory>
#include <iostream>
#include <numeric>
#include <algorithm>

using gsl_vector = double;
gsl_vector *gsl_vector_calloc(std::size_t num)
{
    std::cout << "gsl_vector_calloc: " << num << '\n';
    return static_cast<gsl_vector *>(std::calloc(num, sizeof(double)));
}

void gsl_vector_free(gsl_vector *v)
{
    std::cout << "gsl_vector_free\n";
    std::free(v);
}

double gsl_vector_get(const gsl_vector *v, std::size_t idx)
{
    return v[idx];
}

void gsl_vector_set(gsl_vector *v, std::size_t idx, double value)
{
    v[idx] = value;
}

namespace gsl {

class vector
{
    std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)> v_;
public:

    explicit vector(std::size_t num)
    : v_(gsl_vector_calloc(num), gsl_vector_free)
    {}
    
    double operator[](std::size_t idx) const
    {
        return gsl_vector_get(v_.get(), idx);
    }
    
    void set(std::size_t idx, double value)
    {
        gsl_vector_set(v_.get(), idx, value);
    }
};

}

int main()
{
    gsl::vector v(10);
    
    for(std::size_t i = 0; i < 10; ++i) {
        v.set(i, static_cast<double>(i));
    }
    for(std::size_t i = 0; i < 10; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}
