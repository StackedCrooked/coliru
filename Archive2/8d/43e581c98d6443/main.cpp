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
				n2 *=2; // multiplication par deux
			}
			x /= base_n;
			n += n2; // addition
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
			fractional_part*=2;
			if(x>=base)
			{
				fractional_part+=1;
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
    { // avec des doubles
        std::cout<< "Avec des doubles"<<std::endl;
        std::cout<< "================"<<std::endl;
	    double x=3729652975.0;
	    double base=std::exp(1.0);
	    std::cout.precision(std::numeric_limits<double>::digits10); // 15 décimale de précision (dépend des machines/compilo etc.)
	    std::cout<<"Implémentation fait maison:\t"<< myLog::log(x, base,52) <<std::endl;
        std::cout<<"Implémentation standard:\t"<< std::log(x) / std::log(base)<< std::endl<< std::endl;
    }
    { // avec des long doubles
        std::cout<< "Avec des long doubles"<<std::endl;
        std::cout<< "================"<<std::endl;
        long double x=3729652975.0L; // le suffixe L pour indiquer qu'il s'agit d'un long double
	    long double base=std::exp(1.0L);
	    std::cout.precision(std::numeric_limits<long double>::digits10); // 15 décimale de précision (dépend des machines/compilo etc.)
	    std::cout<<"Implémentation fait maison:\t"<< myLog::log(x, base,63) <<std::endl;
        std::cout<<"Implémentation standard:\t"<< std::log(x) / std::log(base)<< std::endl;
    }
	return 0;
}