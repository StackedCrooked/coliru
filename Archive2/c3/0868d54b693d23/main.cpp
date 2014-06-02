#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

std::stringstream str("1 2 3\n4 5 6\n7 8 9");
    
template <
    class Value,
    class Container       = std::vector<Value>,
    class charT           = char,
    class traits          = std::char_traits<charT>
>
class line_iterator
    : public std::iterator<std::input_iterator_tag, std::vector<Value>>
{
public:
    using value_type      = Value;
    using container_type  = Container;
private:
    std::basic_istream<charT, traits>*      is_;
    std::basic_string<charT, traits>        line;
    std::basic_istringstream<charT, traits> str;
    container_type temp;
    int count = -1;
public:
    line_iterator(std::basic_istream<charT, traits>& is, int count = -1) noexcept
        : is_(&is), count(count)
    { this->read(); }

    constexpr line_iterator() noexcept : is_(nullptr)
    { }
    
    constexpr line_iterator(const line_iterator& rhs) noexcept
        : is_(rhs.is_), temp(rhs.temp), count(rhs.count)
    { };

    constexpr container_type operator*() const noexcept
    {
        return temp;
    }

    line_iterator& operator++()
    {
        this->read();
        return *this;
    }

    line_iterator operator++(int)
    {
        line_iterator copy(*this);
        ++*this;
        return copy;
    }
    
    friend constexpr bool operator==(const line_iterator& lhs,
                                     const line_iterator& rhs) noexcept
    {
        return lhs.is_ == rhs.is_;
    }
    
    friend constexpr bool operator!=(const line_iterator& lhs,
                                     const line_iterator& rhs) noexcept
    {
        return !(lhs == rhs);
    }
private:
    void read()
    {
        temp.clear();
        
        if (is_)
        {
            if (std::getline(*is_, line))
            {
                str.str(line);
                
                if (count == -1)
                    temp.assign(
                    std::istream_iterator<Value, charT, traits>{str}, {});
                else if (0 <= count)
                    std::copy_n(
                        std::istream_iterator<Value, charT, traits>{str},
                        count,
                        std::back_inserter(temp));
            }
            
            if (!*is_)
                is_ = nullptr;

            str.clear();
        }
    }
};

template <
    class Value,
    class Container       = std::vector<Value>,
    class charT           = char,
    class traits          = std::char_traits<charT>
>
line_iterator<Value, Container, charT, traits>
constexpr line_iter(std::basic_istream<charT, traits>& is, int count = -1) noexcept
{
    return line_iterator<Value, Container, charT, traits>{is, count};
}

template<class Value>
constexpr line_iterator<Value> line_iter() noexcept
{
    return line_iterator<Value>{};
}

int main()
{
    std::vector<std::vector<int>> v{line_iter<int>(str), line_iter<int>()};
    
    for (auto a : v)
    {
        for (auto b : a)
            std::cout<<b<<" ";
        std::cout<<"\n";
    }
}