#include <iostream>
#include <vector>
#include <functional>
#include <sstream>
#include <iterator>

namespace detail
{
    template<int... Is>
    struct index { };
    
    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };
    
    template<int... Is>
    struct gen_seq<0, Is...> : index<Is...> { };
}

std::ios_base::iostate
raw_string_get(std::istreambuf_iterator<char> it, std::string& str)
{
    auto& ctype = std::use_facet<std::ctype<char>>(std::locale::classic());
    auto str_it = std::back_inserter(str);
    std::ios_base::iostate err = std::ios_base::goodbit;
    
    do
    {
        *str_it++ = *it++;
        
        if (*it == std::char_traits<char>::eof())
        {
            err |= std::ios_base::eofbit;
            str.erase(std::prev(str.end(), 1));
            return err;
        }
        
        if (str.empty())
            err |= std::ios_base::failbit;
    } while (!ctype.is(ctype.space, *it));
    
    return err;
}

template<int... Is>
std::istream& word_extractor(std::istream& is, std::string& str, detail::index<Is...>)
{
    std::string temp;
    
    
    auto f = [&] {
        std::ios_base::iostate result;
        
        if ((result = raw_string_get(is, temp)) == std::ios_base::goodbit)
        {
            str += temp;
            temp.clear();
        }
        else {
            is.setstate(result);
        }
    };
        
    auto l = { 0, ((Is, f()), 0)... };
    (void)l;
    return is;
}

template<int>
class word_extractor_impl
{
public:
    word_extractor_impl(std::string& value)
        : value_(value)
    { }
    
    template<int N>
    friend std::istream&
    operator>>(std::istream& is, const word_extractor_impl<N>& manip)
    {
        std::istream::sentry ok(is);
        
        if (ok)
            return word_extractor(is, manip.value_, detail::gen_seq<N>());
        return is;
    }
private:
    std::string& value_;
};

template<int N>
word_extractor_impl<N> word_extractor(std::string& str)
{
    return word_extractor_impl<N>(str);
}

int main()
{
    std::stringstream ss("1 bob marely 22");
    int a, b;
    std::string name;
    if (ss >> a >> word_extractor<2>(name) >> b)
    {
        std::cout<<name;
    }
}