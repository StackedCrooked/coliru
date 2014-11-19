#include <boost/function_output_iterator.hpp>
#include <boost/variant.hpp>
#include <boost/bind.hpp>

#include <iostream>

struct serializer : public boost::static_visitor<> {
    template<typename T, typename Out>
        void operator()(T const& x, Out& out) const
    {
        static_assert(boost::is_pod<T>(), "");
        char const* rawp = reinterpret_cast<char const*>(&x);
        std::copy(rawp, rawp+sizeof(T), out);
    }
};

template <typename Variant, typename Out>
Out serialize(Variant const& v, Out into) {
    boost::apply_visitor(boost::bind(serializer(), _1, boost::ref(into)), v);
    return into;
}

template <typename Variant>
size_t serialized_size(Variant const& v) {
    size_t octets = 0;
    serialize(v, boost::make_function_output_iterator([&octets](char) { ++octets; }));
    return octets;
}

#include <boost/array.hpp> // just as a sample

int main() {
    typedef boost::variant<int, double, boost::array<char, 42> > V;

    std::cout << "With int:      " << serialized_size(V(0)) << "\n";
    std::cout << "With double:   " << serialized_size(V(3.14)) << "\n";
    std::cout << "With array:    " << serialized_size(V(boost::array<char,42>())) << "\n";
}
