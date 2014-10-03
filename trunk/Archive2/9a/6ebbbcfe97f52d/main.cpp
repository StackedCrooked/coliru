#include <iostream>
#include <iomanip>
#include <cassert>
#include <cinttypes>
#include <limits>
#include <chrono>
#include <cmath>
  
using clock_type = std::chrono::high_resolution_clock;
  
// Petite fonction pour mesurer les perfs d'un appel de fonction qui
// renvoie un entier.
// (c) 2013, 2014 Luc Hermitte, sous licence BSL (boost)
template <std::size_t N, typename F, typename... F_args>
void perf_f(std::string const& txt, F f, F_args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();
 
    auto res = f(std::forward<F_args>(args)...);
    for (std::size_t i=0; i!=(N-1); ++i) {
        res += f(std::forward<F_args>(args)...);
    }
    auto end   = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << N << " x " << txt << ": " << res << " computed in " << (dur.count()/1000.0) << "ms\n"; //1 ms = 10^6 ns (là c'est plus du microseconde)
}

namespace myLog
{   
    template< typename double_type, std::size_t precision>
    inline constexpr double_type log_impl( double_type x, double_type base,
                                    double_type tmp_integral_part, double_type tmp_pow_integral_part,
                                    double_type tmp_pow_fractional_part, std::size_t rank_fractional_part,
                                    double_type result)
    {
        return rank_fractional_part>=precision? result:
            x>= tmp_integral_part?
                (x>=tmp_integral_part*tmp_integral_part? log_impl<double_type,precision>(x,base,tmp_integral_part*tmp_integral_part, tmp_pow_integral_part*2, 1, 1, result)
                   : log_impl<double_type,precision>(x/tmp_integral_part,base,base, 1, 1, 1, tmp_pow_integral_part+result)
                )
                : (x*x>=base? log_impl<double_type,precision>(x*x/base,base,base, 1, tmp_pow_fractional_part/2, rank_fractional_part+1, tmp_pow_fractional_part/2+result)
                   : log_impl<double_type,precision>(x*x,base,base, 1, tmp_pow_fractional_part/2, rank_fractional_part+1, result)
                );
    }
    
    template< typename double_type>
    inline constexpr double_type log(double_type x, double_type base)
    {
        return x<0? 0:
            x<1? -log<double_type>(1/x,base):
            log_impl<double_type,std::numeric_limits<double_type>::digits>(x, base, base, 1, 1, 1, 0);
    }
}

template <typename double_type>
void bench(double_type x)
{
    const auto nbTests = 100000;
    double_type base=std::exp(static_cast<double_type>(1));
	std::cout.precision(std::numeric_limits<double_type>::digits10); // 15 décimales de précision pour les "double" (dépend des machines/compilo etc.)
    perf_f<nbTests>("myLog::log", [=](double_type x){return myLog::log<double_type>(x,base); }, x);
    perf_f<nbTests>("std::log  ", [](double_type x){return std::log(x);}, x);
}

int main()
{   
    bench(987.6492);
    bench(3729652975.0L);
	return 0;
}