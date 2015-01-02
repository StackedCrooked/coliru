#include <iostream>
#include <ostream>
#include <valarray>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <limits>

#include <cstdlib>
#include <cassert>

using value_type = long double;
using vector = std::valarray< value_type >; // column-vector
using matrix = std::valarray< vector >;

namespace
{

std::ostream &
operator << (std::ostream & out, vector const & v)
{
    for (value_type const & x : v) {
        out << x << ' ';
    }
    return out << '\n';
}

std::ostream &
operator << (std::ostream & out, matrix const & a)
{
    std::size_t const m = a[0].size();
    std::size_t const n = a.size();
    for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            out << a[j][i] << ' ';
        }
        out << '\n';
    }
    return out << '\n';
}

value_type const eps = std::numeric_limits< value_type >::epsilon();
value_type const zero = value_type(0);
value_type const one = value_type(1);

}

int
main()
{
    matrix a{{12, 6, -4},
             {-51, 167, 24},
             {4, -68, -41}};
    std::cout << "A:\n" << a;

    std::size_t const m = a[0].size();
    std::size_t const n = a.size();
    vector rtrace(zero, n);
    for (std::size_t j = 0; j < n; ++j) { // Householder itself
        value_type norm = zero;
        vector & qr_j = a[j];
        for (std::size_t i = j; i < m; ++i) {
            value_type const & qrij = qr_j[i];
            norm += qrij * qrij;
        }
        using std::sqrt;
        norm = sqrt(norm);
        value_type & qrjj = qr_j[j];
        value_type & dj = rtrace[j];
        dj = (zero < qrjj) ? -norm : norm;
        using std::abs;
        value_type f = norm * (norm + abs(qrjj));
        assert(eps < f);
        f = one / sqrt(std::move(f));
        qrjj -= dj;
        for (std::size_t k = j; k < m; ++k) {
            qr_j[k] *= f;
        }
        for (std::size_t i = j + 1; i < n; ++i) {
            vector & qr_i = a[i];
            value_type dot_product = zero;
            for (std::size_t k = j; k < m; ++k) {
                dot_product += qr_j[k] * qr_i[k];
            }
            for (std::size_t k = j; k < m; ++k) {
                qr_i[k] -= qr_j[k] * dot_product;
            }
        }
    }
    std::cout << "QR:\n" << a;
    std::cout << "trace(R):\n" << rtrace;

    matrix q{{1, 0, 0},
             {0, 1, 0},
             {0, 0, 1}};
    for (std::size_t i = 0; i < n; ++i) {
        vector & qi = q[i];
        std::size_t j = n;
        while (0 < j) {
            --j;
            vector & qr_j = a[j];
            value_type s_ = zero;
            for (std::size_t k = j; k < m; ++k) {
                s_ += qr_j[k] * qi[k];
            }
            for (std::size_t k = j; k < m; ++k) {
                qi[k] -= qr_j[k] * s_;
            }
        }
    }
    std::cout << "Q:\n" << q;

    matrix r{{0, 0, 0},
             {0, 0, 0},
             {0, 0, 0}};
    for (std::size_t i = 0; i < n; ++i) {
        r[i][i] = rtrace[i];
        for (std::size_t j = i + 1; j < n; ++j) {
            r[j][i] = a[j][i];
        }
    }
    std::cout << "R:\n" << r;

    matrix qr{{0, 0, 0},
              {0, 0, 0},
              {0, 0, 0}};
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            for (std::size_t k = 0; k < n; ++k) {
                qr[j][i] += q[k][i] * r[j][k];
            }
        }
    }
    std::cout << "Q * R:\n" << qr << std::flush;
    return EXIT_SUCCESS;
}

