#include <boost/variant.hpp>

int main() {
    {
        boost::variant<bool, std::string> v;
        v = "hello"; // is char const(&)[6], converts to bool

        assert(0 == v.which());

        v = static_cast<char const*>("hello");
        assert(0 == v.which());
    }

    // compare to
    {
        boost::variant<bool, char const*> v;
        v = "hello"; // is char const(&)[6]

        assert(1 == v.which()); // now selects the direct match

        v = static_cast<char const*>("hello");
        assert(1 == v.which());
    }
}
