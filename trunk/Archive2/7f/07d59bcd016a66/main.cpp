#include <boost/variant.hpp>
#include <boost/bind.hpp>

#include <boost/array.hpp> // just as a sample
#include <iostream>

namespace serialization {

    namespace customization {
        template<typename T, typename Out, typename R = typename boost::enable_if<boost::is_pod<T>, void>::type>
            void do_serialize(T const& x, Out& out)
            {
                static_assert(boost::is_pod<T>(), "");
                char const* rawp = reinterpret_cast<char const*>(&x);
                std::copy(rawp, rawp+sizeof(T), out);
            }

        template<typename Out>
            void do_serialize(std::string const& x, Out& out)
            {
                do_serialize(x.size(), out);
                for(auto ch : x)
                    do_serialize(ch, out);
            }
    }

    struct serialize_f : public boost::static_visitor<> {
        template<typename Out, typename... T>
            void operator()(boost::variant<T...> const& v, Out& out) const
            {
                boost::apply_visitor(boost::bind(*this, _1, boost::ref(out)), v);
            }

        template<typename T, typename Out>
            void operator()(T const& x, Out& out) const
            {
                using customization::do_serialize; // ADL dispatch
                do_serialize(x, out);
            }
    };
    
    template <typename T, typename Out>
        Out serialize(T const& v, Out out) {
            const static serialize_f _vis {};
            _vis(v, out);
            return out;
        }

}

namespace MyUserTypes {

    struct A {
        std::string name;
        int i;
    };

    template<typename Out> void do_serialize(A const& v, Out& out) { // ADL will find this
        serialization::serialize(v.name, out);
        serialization::serialize(v.i, out);
    }
}

int main() {
    using namespace serialization;
    std::vector<uint8_t> binary_data;
    auto out_inserter = back_inserter(binary_data);

    // variants and custom types
    typedef boost::variant<MyUserTypes::A, boost::array<char, 42> > V;
    MyUserTypes::A myA { "0123456789", 99 };
    V v = boost::array<char,42>();

    serialize(myA, out_inserter);
    serialize(v, out_inserter);
    v = myA;
    serialize(v, out_inserter);

    std::cout << "Bytes in binary_data vector: " << binary_data.size() << "\n";
}
