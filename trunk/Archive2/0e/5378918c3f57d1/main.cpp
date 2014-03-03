#include <boost/unordered_map.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>

namespace hash_examples
{
    struct iequal_to
        : std::binary_function<std::string, std::string, bool>
    {
        iequal_to() {}
        explicit iequal_to(std::locale const& l) : locale_(l) {}

        template <typename String1, typename String2>
        bool operator()(String1 const& x1, String2 const& x2) const
        {
            return boost::algorithm::iequals(x1, x2, locale_);
        }
    private:
        std::locale locale_;
    };

    struct ihash
        : std::unary_function<std::string, std::size_t>
    {
        ihash() {}
        explicit ihash(std::locale const& l) : locale_(l) {}

        template <typename String>
        std::size_t operator()(String const& x) const
        {
            std::size_t seed = 0;

            for(typename String::const_iterator it = x.begin();
                it != x.end(); ++it)
            {
                boost::hash_combine(seed, std::toupper(*it, locale_));
            }

            return seed;
        }
    private:
        std::locale locale_;
    };
}

int main()
{
    using namespace hash_examples;
    boost::unordered_map<std::string, int, ihash, iequal_to> map;
    map.emplace("one",   1);
    map.emplace("two",   2);
    map.emplace("three", 3);

    std::cout << map.at("TWO");
}
