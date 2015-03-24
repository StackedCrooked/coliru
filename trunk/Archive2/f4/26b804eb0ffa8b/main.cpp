#include <string>
#include <memory>

struct base {
    virtual ~base() = 0;
    
    virtual std::string message() const = 0;
};

base::~base() = default;

namespace lib {

std::unique_ptr<base> plugin();
    
} // lib

using namespace std::literals::string_literals;

struct impl: base {
    std::string message() const override
    { return "message from the vanilla plugin"s; }
};

std::unique_ptr<base> lib::plugin()
{ return std::make_unique<impl>(); }