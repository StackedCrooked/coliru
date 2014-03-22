#include<iostream>
#include<tuple>
#include<string>

template <unsigned int A, unsigned int B>
struct FirstClass
{
    static constexpr unsigned int C = A;
    static constexpr unsigned int D = B;
};

template < typename T, const T* const t >
struct SecondClass
{

    static constexpr unsigned int FOR_THIRD_CLASS = T::C;

    //SecondClass knows about a FirstClass instance at compile time
    static constexpr T* const pFirstClass = t;

    //uses FirstClass values, which were computed at compile time, at runtime
    void printFirstClassValues() const {

        //ThirdClass below is an example without pointers or references, which it sounds like you don't need
        std::cout << t -> C << " " << t -> D;
    }

};

template < typename T >
struct ThirdClass
{
    void printSecondClassValue() const {
        std::cout << "\nIn ThirdClass method: " << T::FOR_THIRD_CLASS;
    }
};


static constexpr FirstClass<1,2> fc;

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
  for_each(std::tuple<Tp...> &, FuncT) // Unused arguments are given no names.
  { }

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
  for_each(std::tuple<Tp...>& t, FuncT f)
  {
    f(std::get<I>(t));
    for_each<I + 1, FuncT, Tp...>(t, f);
  }

struct Functor 
{
    template<typename T>
    void operator()(T& t) const { std::cout << t << ", "; }
};

template< typename... Ts >
struct FourthClass{

    std::tuple< Ts... > myTuple;

    //if you need it...
    static constexpr int numberOfTypes = sizeof...(Ts);

    FourthClass(Ts... pack):myTuple(pack...){
    }

    void print(){
        for_each( myTuple, Functor() );
    }

};

//maybe this is better - give it a tuple to begin with
template < typename my_tuple >
class FifthClass{

};

//just use your imagination here - these are ridiculous typedefs that don't ever make sense to use, I'm just showing you how to use FifthClass with a variable number of types
typedef SecondClass< decltype(fc), &fc > SC;
typedef ThirdClass<SC> TC;
typedef FourthClass<TC> FC;
typedef std::tuple<SC,TC,FC> ArbitraryClasses;
typedef std::tuple<SC,TC,FC,ArbitraryClasses> OtherArbitraryClasses;
typedef std::tuple<SC,TC,FC,ArbitraryClasses,OtherArbitraryClasses, int, std::string> MoreArbitraryClasses;

int main(){

    SecondClass<decltype(fc), &fc> sc;
    ThirdClass<decltype(sc)> tc;

    sc.printFirstClassValues();
    tc.printSecondClassValue();


    std::cout << "\nEdit: here's a variadic example..." << std::endl;

    FourthClass < int,unsigned int, short, const char*, int*, std::string > fourth(9,6,19,"this is a string", (int*)0xDEADBEEF, "I could keep going with any cout-able types");
    fourth.print();

    //FifthClass < MoreArbitraryClasses > fifth;  

    return 0;
}