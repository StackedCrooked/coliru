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
    { return "first message from the chocolate plugin"s; }
};

struct impl2: base {
    std::string message() const override
    { return "additional message from the chocolate plugin"s; }
};

std::unique_ptr<base> lib::plugin()
{
    static bool called = false;
    if(!std::exchange(called, true)) {
        return std::make_unique<impl>();
    } else {
        return std::make_unique<impl2>();
    }
}