#include "boost/variant.hpp"
#include <iostream>
#include <string>

namespace compression {
    
struct Plain {
    void compress(std::ostream & os, const std::string & s) { os << s; }
};

struct WithStars {
    void compress(std::ostream & os, const std::string & s) {
        os << "*** " << s << " ***";
    }
};

typedef boost::variant<WithStars, Plain> policy;

struct policy_visitor : boost::static_visitor<> {
    policy_visitor(std::ostream & os, const std::string & s) : os(os), s(s) {}

    template<typename C>
    void operator()(C & c) const { c.compress(os, s); }
    
    std::ostream & os;
    const std::string & s;
};

} // namespace compression

struct Archive {
    template<typename Compressor>
    Archive(const Compressor & c) : compression_policy(c) { }
    
    void archive(std::ostream & os, const std::string & s) {
        compression::policy_visitor v{os, s};
        compression_policy.apply_visitor(v);
    }
    
    mutable compression::policy compression_policy;
};


int main() {
    Archive arch{compression::WithStars{}};
    arch.archive(std::cout, "some text");
}