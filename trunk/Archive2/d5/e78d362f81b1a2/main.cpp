#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4351 4996)
#endif

#include <iostream>
#include <algorithm>
#include <sstream>

namespace marshal
{
    template<std::size_t capacity, bool clean = false>
    class string
    {
    private:
        char buffer[capacity] = {};

        void assign(std::string const& text)
        {
            auto index = std::min(text.length(), capacity);
            std::copy_n(text.begin(), index, buffer);

            if (clean)
            {
                std::fill_n(buffer + index, capacity - index, '\0');
            }
            else
            {
                buffer[std::min(index, capacity - 1)] = '\0';
            }

            // Temporary, for debugging, null chars are shown as dots
            std::transform(cbegin(), cend(), begin(), [](char const& c)
            {
                return c ? c : '.';
            });
        }

    public:
        // Constructors
        string()
        {}

        // Copy
        template<std::size_t R, bool C>
        string(string<R, C> const& other)
            : string(std::string(other))
        {}
        string(char const* text)
            : string(std::string(text))
        {}

        string(std::string const& text)
        {
            assign(text);
        }

        // Conversions
        operator std::string() const
        {
            return std::string(buffer, buffer + capacity);
        }

        // Indexing
        char& operator [](std::size_t index)
        {
            return buffer[index];
        }

        // Dereference
        char& operator *()
        {
            return *buffer;
        }

        // Bool conversion, true if non-empty
        explicit operator bool() const
        {
            return buffer[0] != '\0';
        }

        // Container functions
        char* begin()
        {
            return buffer;
        }

        char* end()
        {
            return buffer + capacity;
        }

        char const* cbegin()
        {
            return buffer;
        }

        char const* cend()
        {
            return buffer + capacity;
        }

        char const* data()
        {
            return buffer;
        }

        std::size_t size()
        {
            return capacity;
        }
        std::size_t max_size()
        {
            return capacity;
        }

        // Stream operators
        template<std::size_t N, bool C>
        friend std::ostream operator <<(std::ostream& stream, string const& str);
        template<std::size_t N, bool C>
        friend std::istream operator >>(std::istream& stream, string& str);
    };

    template<std::size_t N, bool C>
    std::ostream& operator <<(std::ostream& stream, string<N, C> const& str)
    {
        return stream << std::string(str);
    }

    template<std::size_t N, bool C>
    std::istream& operator >>(std::istream& stream, string<N, C>& str)
    {
        std::string value;
        stream >> value;
        str.assign(value);
        return stream;
    }
}

struct foo
{
    bool first;
    marshal::string<31, true> second;
    float third;
    marshal::string<5> fourth;
    marshal::string<4> fifth;
    int sixth;
};

int main()
{
    foo x;
    x.second = "nya~";
    x.fourth = std::string("me");
    x.fifth = x.second;

    marshal::string<15> foo;
    foo = "hello";
    std::cout << foo << " " << sizeof foo << std::endl;
    foo = std::string("bar");
    std::cout << foo << " " << sizeof foo << std::endl;
    char test[4] = {'a', 'b', 'c'};
    foo = test;
    std::cout << foo << " " << sizeof foo << std::endl;
    foo = "this is a very long string";
    std::cout << foo << " " << sizeof foo << std::endl;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
