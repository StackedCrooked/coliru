#define BOOST_VARIANT_MINIMIZE_SIZE

#include <boost/variant.hpp>
#include <type_traits>
#include <functional>
#include <iostream>
#include <utility>

using namespace std;

/****************************************************************/
// Boost.Variant requires result_type:
template<typename T, typename F>
struct ResultType
{
     mutable F f;
     using result_type = T;

     template<typename ...Args> T operator()(Args&& ...args) const
     {
         return f(forward<Args>(args)...);
     }
};

template<typename T, typename F>
auto make_result_type(F &&f)
{
    return ResultType<T, typename decay<F>::type>{forward<F>(f)};
}
/****************************************************************/
// Proof-of-Concept
template<typename Base, typename ...Ts>
struct SubVariant
{
    Base shared_data;
    boost::variant<Ts...> sub;

    template<typename Visitor>
    friend auto apply(Visitor visitor, SubVariant &operand)
    {
        using result_type = typename common_type
        <
            decltype( visitor(shared_data, declval<Ts&>()) )...
        >::type;

        return boost::apply_visitor(make_result_type<result_type>([&](auto &x)
        {
            return visitor(operand.shared_data, x);
        }), operand.sub);
    }
};
/****************************************************************/
// Demo:

struct ThingData
{
    int f1;
    int f2;
};

struct Summator
{
    void doAction1(ThingData &self)  { self.f1 += self.f2; }
    const char* type_name() { return "Summator"; }
};

struct Substractor
{
    void doAction1(ThingData &self)  { self.f1 -= self.f2; }
    const char* type_name() { return "Substractor"; }
};

using Thing = SubVariant<ThingData, Summator, Substractor>;

int main()
{
    auto test = [](auto &self, auto &sub)
    {
        sub.doAction1(self);
        cout << sub.type_name() << " " << self.f1 << " " << self.f2 << endl;
    };
    
    Thing x = {{5, 7}, Summator{}};
    apply(test, x);
    x.sub = Substractor{};
    apply(test, x);

    cout << "size: " << sizeof(x.sub) << endl;
}