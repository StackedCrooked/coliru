#include <system_error>

namespace NS { enum class X {a,b,c}; }
using NS::X;

class X_category : public std::error_category
{
public:
    virtual const char *name() const noexcept override { return "X"; }
    virtual std::string message(int) const override { return ""; }
};

inline const std::error_category& X_category()
{
    static class X_category c; return c;
}

namespace std { template<> struct is_error_code_enum<X> : public std::true_type{}; }

namespace NS {
    inline std::error_code make_error_code(X result)
    {
        return std::error_code(static_cast<int>(result), X_category());
    }
}

int main()
{
    std::error_code e = X::a; // does not work !!
}