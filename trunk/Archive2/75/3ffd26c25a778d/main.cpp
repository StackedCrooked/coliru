#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <fstream>
#include <iostream>

using namespace boost; // brevity

//////////////////
// This is the utility part that I had created in earlier answers:
namespace util {
    template<typename T, class...Fs> struct visitor_t;

    template<typename T, class F1, class...Fs>
    struct visitor_t<T, F1, Fs...> : F1, visitor_t<T, Fs...>::type {
        typedef visitor_t type;
        visitor_t(F1 head, Fs...tail) : F1(head), visitor_t<T, Fs...>::type(tail...) {}

        using F1::operator();
        using visitor_t<T, Fs...>::type::operator();
    };

    template<typename T, class F> struct visitor_t<T, F> : F, boost::static_visitor<T> {
        typedef visitor_t type;
        visitor_t(F f) : F(f) {}
        using F::operator();
    };

    template<typename T=void, class...Fs>
    typename visitor_t<T, Fs...>::type make_visitor(Fs...x) { return {x...}; }
}

using util::make_visitor;

namespace my_types {
    //////////////////
    // fake types for demo only
    struct A1 {
        std::string data;
    };

    struct A2 {
        double data;
    };

    struct A3 {
        std::vector<int> data;
    };

    // some operations defined on A1,A2...
    template <typename A> static inline void serialize(A& ar, A1& a, unsigned) { ar & a.data; } // using boost serialization for brevity
    template <typename A> static inline void serialize(A& ar, A2& a, unsigned) { ar & a.data; } // using boost serialization for brevity
    template <typename A> static inline void serialize(A& ar, A3& a, unsigned) { ar & a.data; } // using boost serialization for brevity

    static inline void display(std::ostream& os, A3 const& a3) { os << "display A3: " << a3.data.size() << " elements\n"; }
    template <typename T> static inline void display(std::ostream& os, T const& an) { os << "display A1 or A2: " << an.data << "\n"; }

    //////////////////
    // our variant logic
    using AnyA = variant<A1,A2,A3>;

    //////////////////
    // test data setup
    AnyA generate() { // generate a random A1,A2...
        switch (rand()%3) {
            case 0: return A1{ "data is a string here" };
            case 1: return A2{ 42 };
            case 2: return A3{ { 1,2,3,4,5,6,7,8,9,10 } };
            default: throw std::invalid_argument("rand");
        }
    }

}

using my_types::AnyA;

void write_archive(std::string const& fname) // write a test archive of 10 random AnyA
{
    std::vector<AnyA> As;
    std::generate_n(back_inserter(As), 10, my_types::generate);

    std::ofstream ofs(fname, std::ios::binary);
    archive::text_oarchive oa(ofs);

    oa << As;
}

//////////////////
// logic under test
template <typename F>
void process_archive(std::string const& fname, F process) // reads a archive of AnyA and calls the processing function on it
{
    std::ifstream ifs(fname, std::ios::binary);
    archive::text_iarchive ia(ifs);

    std::vector<AnyA> As;
    ia >> As;

    for(auto& a : As)
        apply_visitor(process, a);
}

int main() {
    srand(time(0));

    write_archive("archive.txt");

    // the following is c++11/c++1y lambda shorthand for entirely compiletime
    // generated code for the specific type(s) received
    auto visitor = make_visitor(
        [](my_types::A2& a3) { 
                std::cout << "Skipping A2 items, just because we can\n";
                display(std::cout, a3);
            },
        [](auto& other) { 
                std::cout << "Processing (other)\n";
                display(std::cout, other);
            }
        );

    process_archive("archive.txt", visitor);
}