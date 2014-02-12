#include <cassert>
#include <complex>
#include <vector>
#include <iostream>

typedef double Real;
typedef std::complex<Real> Complex;

template<typename T>
class Matrix
{
public:
    Matrix() = default;
    template<typename U>
    Matrix(const Matrix<U> &other)
        : m_(other.m()), n_(other.n()),
          data_(other.data_.begin(), other.data_.end()) { }
    Matrix(size_t m, size_t n) : m_(m), n_(n), data_(m*n) { }
    Matrix(size_t m, size_t n, const T &initial)
        : m_(m), n_(n), data_(m*n, initial) { }

    size_t m() const { return m_; }
    size_t n() const { return n_; }
    size_t size() const {
        assert(m_*n_ == data_.size());
        return data_.size();
    }

    const T &operator()(size_t i, size_t j) const { return data_[i*m_ + j]; }
    T       &operator()(size_t i, size_t j)       { return data_[i*m_ + j]; }

    void fill(const T &value) {
        std::fill(data_.begin(), data_.end(), value);
    }

    template <typename T2>
    Matrix &operator+=(const Matrix<T2> &other) {
        assert(dim_match(other));
        for (int i = 0; i < size(); ++i) {
            data_[i] += other.data_[i];
        }
        return *this;
    }

    template <typename T1, typename T2>
    friend Matrix<typename std::common_type<T1, T2>::type> 
        operator+(Matrix<T1> const& a, Matrix<T2> const& b);

    friend std::ostream &operator<<(std::ostream &o, const Matrix &m) {
        if (m.size() == 0) {
            o << "()" << std::endl;
            return o;
        }
        for (int i = 0; i < m.m(); ++i) {
            o << "( ";
            for (int j = 0; j < m.n() - 1; ++j) {
                o << m(i,j) << ", ";
            }
            o << m(i, m.n() - 1) << " )" << std::endl;
        }
        return o;
    }

private:
    template <typename T2>
    bool dim_match(const Matrix<T2> &other) const {
        return n_ == other.n_ && m_ == other.m_;
    }

private:
public:
    int m_, n_;
    typedef std::vector<T> Store;
    Store data_;
};

template <typename T1, typename T2>
Matrix<typename std::common_type<T1, T2>::type> 
    operator+(Matrix<T1> const& a, Matrix<T2> const& b)
{
    Matrix<typename std::common_type<T1, T2>::type> result(a.m(), a.n());
    return (result += b);
}

int main() {
    Matrix<Real> A(2,3, 1.);
    Matrix<Complex> B(2,3, Complex(0,1));
    auto C = A + B;
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;
}
