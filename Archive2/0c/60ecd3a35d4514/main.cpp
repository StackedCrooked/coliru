#include <iostream>
#include <iomanip> 
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/math/special_functions/round.hpp>
#include <boost/format.hpp>

typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<20> > cpp_dec_float_20;

inline cpp_dec_float_20 dec_round(const cpp_dec_float_20& v, int p)
{
    const cpp_dec_float_20 DEC_TEN = 10;
    cpp_dec_float_20 dec_p = boost::multiprecision::pow(DEC_TEN, p); // need cache
    return boost::math::round(v * dec_p) / dec_p;
}

struct Archiver {
    template<typename T> 
    void operator & (T& v) {
        std::cout << v << ", ";
    }
};

void showInternal(const char* s)
{
    cpp_dec_float_20 f(s);
    std::cout << "#float value = " << f << ", order= " << f.backend().order() << std::endl;
    std::cout << "#internal = ";
    Archiver ar;
    f.backend().serialize(ar, 0);
    std::cout << "END" << std::endl << std::endl;
}

int main()
{
    cpp_dec_float_20 b = 8000;
#if 0
b /= 3;
    std::cout << std::setprecision(30);
    std::cout << "size: " << sizeof(cpp_dec_float_20) << ", digits: " << std::numeric_limits<cpp_dec_float_20>::digits << std::endl;
    std::cout << "result = " << b << std::endl;
    std::cout << "rounded result = " << boost::math::round(b) << std::endl;
    std::cout << "rounded result = " << dec_round(b, -1) << std::endl;
    
    cpp_dec_float_20 b2("2666.67");
    cpp_dec_float_20 b3 = dec_round(b, 2);
    std::cout << " equal? " << (dec_round(b, 2) == b2) << std::endl;
    std::cout << " diff = " << (b3 - b2) << std::endl;
    std::string s = b3.str();
    std::cout << "str = " << s << std::endl;
    std::cout << "boost formated = " << boost::format("%.4f") % b3 << std::endl;
    std::cout << "stream formated = " << std::setprecision(4) << std::fixed << b3 << std::endl;
    
    std::cout << std::setprecision(20);
    cpp_dec_float_20 testvalue("12345.67890987654321");
    std::cout << "origin value:" << testvalue << std::endl;
    cpp_dec_float_20 partvalue = testvalue.backend().extract_integer_part();
    std::cout << "part value:" << partvalue << std::endl;
    //std::cout << "exp: " << testvalue.backend().exp << std::endl;
    
    double mantissa;
    boost::int32_t exponent;
    testvalue.backend().extract_parts(mantissa, exponent);
    std::cout << "mantissa: " << mantissa << ", exp: " << exponent << std::endl;
    
    showInternal("0.001234567");
    showInternal("-0.001234567");
    showInternal("1234567890987654321");
    showInternal("-1234567890987654321");
    showInternal("12345.67890987654321");
    showInternal("-12345.67890987654321");
    showInternal("123456789098765432.1");
    showInternal("9999999912345678909876543212345.67890987654321");
#endif


cpp_dec_float_20 tmpfee("0.29");
    cpp_dec_float_20 usageV =60;
    cpp_dec_float_20 unitV("60");
	cpp_dec_float_20 feeV;
	std::cout<<"tmpfee:"<<tmpfee.str().c_str()<<std::endl;
	std::cout<<"usageV:"<<usageV.str().c_str()<<std::endl;
	std::cout<<"unitV:"<<unitV.str().c_str()<<std::endl;
	feeV = (tmpfee *usageV)/unitV;
    std::cout<<"---" << (tmpfee *usageV)<<std::endl;
    std::cout<<"---" << (tmpfee *usageV)/60<<std::endl;
    std::cout<<"---" << (tmpfee *usageV)/unitV<<std::endl;
    std::cout<<"---" << feeV << std::endl;
	std::cout<<"##feeV:"<<feeV.str()<<std::endl;
    
    
	feeV = usageV*tmpfee;
	std::cout<<"feeV:"<<feeV.str().c_str()<<std::endl;
	int unitVV =60;
	feeV = usageV*tmpfee /60;
	std::cout<<"feeV:"<<feeV.str().c_str()<<std::endl;
    
    return 0;
}
