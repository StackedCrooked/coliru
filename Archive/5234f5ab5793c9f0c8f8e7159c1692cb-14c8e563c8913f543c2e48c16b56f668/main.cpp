#include <exception>
#include <utility>
#include <string>

struct fixed_runtime_error : virtual std::exception {
    fixed_runtime_error(std::string const& s) : s(s) {}
    fixed_runtime_error(std::string&& s) : s(std::move(s)) {}

    char const* what() const noexcept override { return s.data(); }

private:
    std::string s;
};

struct a_error : fixed_runtime_error {
    a_error() : fixed_runtime_error("a") {}
};
struct b_error : fixed_runtime_error {
    b_error() : fixed_runtime_error("b") {}
};

struct ab_error : a_error, b_error {
    char const* what() const noexcept override { return "ab"; }
};

int main(){
    try {
        throw ab_error();
    } catch(std::exception const& e) {
    }
}