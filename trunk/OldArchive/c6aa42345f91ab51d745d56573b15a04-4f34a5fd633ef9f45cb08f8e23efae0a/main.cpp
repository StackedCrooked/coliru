

template<bool isfloat, bool negative> struct best_numeric_type {typedef long double type;};
template<> struct best_numeric_type<false, true> {typedef long long type;};
template<> struct best_numeric_type<false, false> {typedef unsigned long long type;};

template<class T> struct best_common_numeric_type1 {
    static const bool isfloat=false;
    static const bool negative=false;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<char> {
    static const bool isfloat=false;
    static const bool negative=true;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<signed char> {
    static const bool isfloat=false;
    static const bool negative=true;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<short> {
    static const bool isfloat=false;
    static const bool negative=true;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<int> {
    static const bool isfloat=false;
    static const bool negative=true;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<long> {
    static const bool isfloat=false;
    static const bool negative=true;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<long long> {
    static const bool isfloat=false;
    static const bool negative=true;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<float> {
    static const bool isfloat=true;
    static const bool negative=false;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<double> {
    static const bool isfloat=true;
    static const bool negative=false;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<> struct best_common_numeric_type1<long double> {
    static const bool isfloat=true;
    static const bool negative=false;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};

template<class First, class Second>
struct best_common_numeric_type2 {
    static const bool isfloat = best_common_numeric_type1<First>::isfloat |  best_common_numeric_type1<Second>::isfloat;
    static const bool negative = best_common_numeric_type1<First>::negative |  best_common_numeric_type1<Second>::negative;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<class First, class Second, class Third>
struct best_common_numeric_type3 {
    static const bool isfloat = best_common_numeric_type2<First, Second>::isfloat |  best_common_numeric_type1<Third>::isfloat;
    static const bool negative = best_common_numeric_type2<First, Second>::negative |  best_common_numeric_type1<Third>::negative;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<class First, class Second, class Third, class Fourth>
struct best_common_numeric_type4 {
    static const bool isfloat = best_common_numeric_type3<First, Second, Third>::isfloat |  best_common_numeric_type1<Fourth>::isfloat;
    static const bool negative = best_common_numeric_type3<First, Second, Third>::negative |  best_common_numeric_type1<Fourth>::negative;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
template<class First, class Second, class Third, class Fourth, class Fifth>
struct best_common_numeric_type5 {
    static const bool isfloat = best_common_numeric_type4<First, Second, Third, Fourth>::isfloat |  best_common_numeric_type1<Fifth>::isfloat;
    static const bool negative = best_common_numeric_type4<First, Second, Third, Fourth>::negative |  best_common_numeric_type1<Fifth>::negative;
    typedef typename best_numeric_type<isfloat, negative>::type type;
};
       
       
#include <typeinfo>
#include <iostream>       
void printer(long double) {std::cout << "long double\n";}
void printer(unsigned long long) {std::cout << "ull\n";}
void printer(long long) {std::cout << "ll\n";}
void printer(...) {std::cout << "else\n";}
       
int main() {
    printer(best_common_numeric_type5<long, unsigned long, float, double, int>::type());
    printer(best_common_numeric_type2<unsigned int, unsigned long>::type());
    printer(best_common_numeric_type2<signed int, signed long>::type());
    printer(best_common_numeric_type2<signed int, unsigned int>::type());
    printer(best_common_numeric_type2<signed int, unsigned long>::type());
    printer(best_common_numeric_type2<float, char>::type());
}