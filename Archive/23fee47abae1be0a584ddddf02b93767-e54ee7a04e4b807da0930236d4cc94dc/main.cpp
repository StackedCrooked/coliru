#include <stdexcept>
#include <functional>
#include <map>
#include <iostream>

using namespace std;

#define lambda(U, E) [](U) {E;}

namespace sho
{
    template<typename F>
    class pattern
    {
        public:
            typedef bool(*function)(F);

            // Constructors
            pattern(function f) : fun(f) {}
            pattern(const F& v) // if the user wants a specific value based case.
            {
                auto tmp = [](F v1, F v2) { return v1 == v2; };
                fun = std::bind<bool>(tmp, std::placeholders::_1, v);
            }

            bool operator()(F v) // does the value match the pattern ?
            {
                return fun(v);
            }
            
            bool operator()(const F& v) const
            {
                return fun(v);
            }

            // Operator to use the syntax : sho::pattern >> function
            template<typename E>
            std::pair<pattern<F>, std::function<E(F)>> operator>>(std::function<E(F)> f) const
            {
                return std::pair<pattern<F>, std::function<E(F)>>(*this, f);
            }

            template<typename E>
            std::pair<pattern<F>, std::function<E(F)>> operator>>(E v) const
            {
                auto f = [v](F x) { return v; };
                return std::pair<pattern<F>, std::function<E(F)>>(*this, std::function<E(F)>(f));
            }

        private:
            std::function<bool(F)> fun;
    };

    // Otherwise is a pattern that is always matched.
    template<typename F>
    pattern<F> otherwise()
    {
        return pattern<F>([](F x) { return true; });
    }

    // lesser operator needed by std::map.
    template<typename F>
    bool operator<(const sho::pattern<F>& v1, const sho::pattern<F>& v2)
    {
        return &v1 > &v2;
    }
}//;

namespace sho
{
    // The U type is the type of the entering expression.
    // The E type is the type of the output.
    template <typename U, typename E>
    class match
    {
        public:
            typedef typename std::map<sho::pattern<U>, std::function<E(U)>> patt_list;

            match(const U& expr) : value(expr) {}
            E with(patt_list patts) // "with" function that executes the matching.
            {
                for(typename patt_list::iterator it = patts.begin(); it != patts.end(); it++) // For each pattern, we test the return value.
                {
                    //sho::pattern<U> patt(it->first);

                    //if(patt(value))
                    if(it->first(value))
                        return it->second(value);
                }

                // No pattern verified the value set to the system.
                throw std::range_error("unexhaustive pattern matching system");
            }

        private:
            U value;
    };
}

/* operator| to use the syntax :

      sho::pattern<int>(0)  >> f0
    | sho::pattern<int>(1)  >> f1
    | sho::pattern<int>(2)  >> f2
    | sho::otherwise<int>() >> f3
 */

template <typename U, typename E>
std::map<U, E> operator|(std::map<U, E> m, std::pair<U, E> p)
{
    m[p.first] = p.second;
    return m;
}

template <typename U, typename E>
std::map<U, E> operator|(std::pair<U, E> p1, std::pair<U, E> p2)
{
    return std::map<U, E>( { p1, p2 } );
}

using namespace sho;

int main(void) {
    auto f = [](int x)
{
    return x > 0;
};

int valeur=42;

std::string s = sho::match<int, std::string>(valeur).with
(
    sho::otherwise<int>() >> std::string("negatif !")
    | sho::pattern<int>(f)  >> std::string("positif !")
    | sho::pattern<int>(0)  >> std::string("zero !")
);
    cout << s <<endl;
    return 0;
}
