#include <iostream>
#include <cmath>
#include <cassert>
#include <cinttypes>
#include <limits>

namespace myLog
{
    template< typename double_type>
	inline double_type find_integral_part(double_type x, double_type const base, uint64_t& n)
	{
		assert(x >= 1);
		n = 0;
		while (x >= base)
		{
			double_type base_n = base;
			double_type base_n_2 = base * base;
			uint64_t n2 = 1;
			while (x >= base_n_2)
			{
				base_n = base_n_2;
				base_n_2 *= base_n_2; // il faut gerer le cas où bas_n_2 dépasse la borne maximale de la représentation des nombres flotants gérée
				n2 <<=1; // multiplication par deux
			}
			x /= base_n;
			n |= n2; // addition
		}
		return x;
	}

	template< typename double_type>
	inline double_type log(double_type x, double_type const base, uint8_t const precision)
	{
		assert(x>0);
		assert(base>0 && base!=1);
		assert(precision<64);
		if(x<1) return log(1/x,base,precision);
		uint64_t fractional_part=0;
		uint64_t integral_part;
		x=find_integral_part(x, base,integral_part);
		for(uint16_t itr=0;itr<precision;++itr)
		{
			x*=x;
			fractional_part<<=1;
			if(x>=base)
			{
				fractional_part|=1;
				x/=base;
			}
		}
		return integral_part+((double_type)fractional_part)/(1LLU<<precision);
	}

	template <typename double_type>
	double_type log_serie_entiere(double_type x,uint32_t const precision) // suuuuper lente à l'execution et pas assez puissante pour avoir une bonne précision avant la virgule tellement c'est pas adapté!
	{
		assert(x>0);
		if(x>1) return -log_serie_entiere(1/x,precision);
		double_type result=0;
		double_type x_n=1-x;
		for(uint32_t itr=1;itr< precision;++itr)
		{
			result-=x_n/itr;
			x_n*=1-x;
		}
		return result;
	}

} // namespace


int main()
{
	double x=3729652975.0;
	double base=std::exp(1.0);
	std::cout.precision(std::numeric_limits<double>::digits10); // 15 décimale de précision (dépend des machines/compilo etc.)
	std::cout<<	myLog::log(x, base,52) <<" "<<	std::log(x) / std::log(base)<< std::endl;
	return 0;
}