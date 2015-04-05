#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>

int main() {
    namespace mp = boost::multiprecision;
    //v += 6 * ceil((sqrt(uMax * uMax - candidate) - v) / 6);
    {
        using BF = mp::cpp_bin_float_100;
        using BI = mp::cpp_int;
        BI v = 1, uMax = 9, candidate = 1;

#ifdef DEBUG
        BF tmp1(uMax * uMax - candidate);
        BF tmp2(sqrt(BF(uMax * uMax - candidate)) - BF(v));
        BF tmp3(ceil(tmp2 / 6));
        BI tmp4(tmp3.convert_to<BI>());
        std::cout << tmp1 << " " << tmp2 << " " << tmp3 << " " << tmp4 << "\n";
#endif

        v += 6*ceil((sqrt(BF(uMax * uMax - candidate)) - BF(v)) / 6).convert_to<BI>();
    }

    {
        using BF = mp::number<mp::cpp_bin_float_100::backend_type, mp::et_off>;
        using BI = mp::number<mp::cpp_int::backend_type, mp::et_off>;
        BI v = 1, uMax = 9, candidate = 1;

        v += 6 * ceil((sqrt(BF(uMax * uMax - candidate)) - BF(v)) / 6).convert_to<BI>();
    }

    {
        using BF = mp::number<mp::cpp_dec_float_100::backend_type, mp::et_off>;
        BF v = 1, uMax = 9, candidate = 1;

        v += 6 * ceil((sqrt(uMax * uMax - candidate) - v) / 6);
    }
}
