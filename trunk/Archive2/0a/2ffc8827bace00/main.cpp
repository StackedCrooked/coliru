#include <iostream>
#include <vector>

namespace adapter {

// vector traits struct - base template
template <typename vector_type>
struct vector_traits {
    typedef typename vector_type::value_type value_type;
    
    static vector_type allocate(const value_type& v, size_t n) {
        return vector_type(n, v);
    }

    static vector_type allocate(const value_type* v, size_t n) {
        return vector_type(v, v + n);
    }
};

// matrix traits struct - base template
template <typename matrix_type>
struct matrix_traits {
    typedef typename matrix_type::value_type value_type;

    static matrix_type allocate(size_t nr, size_t nc, const value_type& v) {
        return matrix_type(nr, nc, v);
    }
};

template <typename vector_type, typename value_type = typename vector_traits<vector_type>::value_type>
vector_type allocate(const value_type& v, size_t n) {
    return vector_traits<vector_type>::allocate(v, n);
}

template <typename vector_type, typename value_type = typename vector_traits<vector_type>::value_type>
vector_type allocate(const value_type* v, size_t n) {
    return vector_traits<vector_type>::allocate(v, n);
}

template <typename matrix_type>
matrix_type allocate(size_t nr, size_t nc, const typename matrix_traits<matrix_type>::value_type& v) {
    return matrix_traits<matrix_type>::allocate(nr, nc, v);
}

} // namespace adapter

namespace test {

typedef std::vector<double> vector_double;

class matrix_double {
    public:
        matrix_double(double v, size_t r, size_t c)
            : data(r*c, v) {}
    private:
        std::vector<double> data;
};

} // namespace test

namespace adapter {

template<> struct matrix_traits<test::matrix_double> {
    typedef double value_type;

    static test::matrix_double allocate(size_t r, size_t c, const double& v) {
        return test::matrix_double(v, r, c);
    }
};

} // namespace adapter

int main() {
    // Test allocation of vector filled with zeros
    {
        std::vector<double> v = adapter::allocate<std::vector<double> >(0., 10);
    }

    // Test allocation of vector from array
    {
        double a[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 0.};
        std::vector<double> v = adapter::allocate<std::vector<double> >(a, 10);
    }

    // Test allocation of matrix filled with zeros
    {
        test::matrix_double m = adapter::allocate<test::matrix_double>(3, 3, 0.);
    }

    std::cout << "All OK!\n";
    return 0;
}
