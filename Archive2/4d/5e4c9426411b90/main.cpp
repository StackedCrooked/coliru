#include <cmath>
#include <iomanip>
#include <iostream>

const double ExtDecimalArray[9]={ 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0 };

inline
double mt4NormalizeDouble(const double val,int digits)
{
    if(digits<0) digits=0;
	if(digits>8) digits=8;
	//----
	const double p=ExtDecimalArray[digits];
	return((val>=0.0) ? (double(int(val*p+0.5000001))/p) : (double(int(val*p-0.5000001))/p));
}

int main()
{
    {
        double close_price = 1.21077;
    double open_price = 1.21072;
    int symbol_digits = 5;
        
    double normalized_close_price = mt4NormalizeDouble(close_price, symbol_digits);
    double normalized_open_price = mt4NormalizeDouble(open_price, symbol_digits);

	int normalized_close_price_int = static_cast<int>(normalized_close_price * std::pow(10.0, symbol_digits));
	int normalized_open_price_int = static_cast<int>(normalized_open_price * std::pow(10.0, symbol_digits));

	int trade_spread = std::abs(normalized_close_price_int - normalized_open_price_int);
    
    std::cout << std::fixed << std::setprecision(15) << "normalized_close_price: " << normalized_close_price << '\n'
            << std::fixed << std::setprecision(15) << "normalized_open_price: " << normalized_open_price << '\n'
            << "normalized_close_price_int: " << normalized_close_price_int << '\n'
            << "normalized_open_price_int: " << normalized_open_price_int << '\n'
            << "trade_spread: " << trade_spread << '\n';
    }
    
       
       std::cout << "=========================== \n";
       
    {
        double close_price = 1.21077;
    double open_price = 1.21072;
    int symbol_digits = 5;

    int normalized_close_price_int = static_cast<int>(mt4NormalizeDouble(close_price * std::pow(10.0, symbol_digits), 0));
	int normalized_open_price_int = static_cast<int>(mt4NormalizeDouble(open_price * std::pow(10.0, symbol_digits), 0));

	int trade_spread = std::abs(normalized_close_price_int - normalized_open_price_int);
    
    std::cout 
            << "normalized_close_price_int: " << normalized_close_price_int << '\n'
            << "normalized_open_price_int: " << normalized_open_price_int << '\n'
            << "trade_spread: " << trade_spread << '\n';
    }
}