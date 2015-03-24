#include <string>
#include <memory>

using namespace std::literals::string_literals;

struct base {
    virtual ~base() = 0;
    
    virtual std::string message() const = 0;
};

base::~base() = default;

struct impl: base {
    std::string message() const override
    { return "impl"s; }
};

struct impl2: base {
    std::string message() const override
    { return "impl2"s; }
};

int main()
{
    std::unique_ptr<base> p = std::make_unique<impl>();
    p->message();
    p = std::make_unique<impl2>();
    p->message();
}