#include <iostream>

template<typename Functor>
struct manipulator_type {
    Functor functor;
    
    template<typename Stream>
    void operator()(Stream&& stream)
    {
        functor(std::forward<Stream>(stream));
    }
    
    template<typename Stream>
    void operator()(Stream&& stream) const
    {
        functor(std::forward<Stream>(stream));
    }
};

template<typename Stream, typename Functor>
// Return type as inspired by H. Hinnant
Stream& operator<<(Stream&& stream, manipulator_type<Functor> const& m)
{
    m(stream);
    return stream;
}

template<typename Stream, typename Functor>
// Return type as inspired by H. Hinnant
Stream& operator<<(Stream&& stream, manipulator_type<Functor>&& m)
{
    m(stream);
    return stream;
}

template<typename Functor>
manipulator_type<Functor> manipulator(Functor&& functor)
{ return { std::forward<Functor>(functor) }; }

auto newlines = [](int n)
{
    return manipulator([n](std::ostream& os)
    {
        for(int i = 0; i != n; ++i) os << '\n';
    });
};

int main()
{
    std::cout << "Hello" << newlines(3) << "World" << newlines(1);
}