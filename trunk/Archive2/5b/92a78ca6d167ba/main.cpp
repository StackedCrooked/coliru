#include <iostream>

#define USE_RVALUE_REF_PLUS

class Int
{
    int n_;

public:
    static int cnt;

    explicit Int(int n) noexcept : n_(n) {
        std::cout << "Int(" << n_ << ")\n";
    }

    Int(const Int& rhs) : n_(rhs.n_) {
        std::cout << "Int(const Int &) [" << n_ << "]\n";
    }

    Int(Int&& rhs) : n_(rhs.n_) {
        std::cout << "Int(Int &&) [" << n_ << "]\n";
    }

    Int& operator=(const Int& rhs) {
        std::cout << "Int& operator=(const Int&)\n";
        n_ = rhs.n_;
        return *this;
    };

    Int& operator=(Int&& rhs) {
        std::cout << "Int& operator=(Int&&)\n";
        n_ = rhs.n_;
        return *this;
    };

    ~Int() {
        std::cout << "~Int()[" << n_ << "]\n";
        ++cnt;
    }

    int n() const { return n_;}

    // we can also add overloads for Int&& rhs

    Int& operator+=(const Int& rhs) & {
        std::cout << "Int& operator+=(const Int& rhs) & [" << n_ << " " << rhs.n_ << "]\n";
        n_ += rhs.n_;
        return *this;
    }

    Int&& operator+=(const Int& rhs) && {
        std::cout << "Int&& operator+=(Int&& rhs) && [" << n_ << " " << rhs.n_ << "]\n";
        n_ += rhs.n_;
        return std::move(*this);
    }

    Int operator+(const Int& rhs) const & {
        std::cout << "Int operator+(const Int& rhs) const & [" << n_ << " " << rhs.n_ << "]\n";
        return Int(n_ + rhs.n_);
    }

#ifdef USE_RVALUE_REF_PLUS
    Int&& operator+(const Int& rhs) && {
        std::cout << "Int&& operator+(const Int& rhs) && [" << n_ << " " << rhs.n_ << "]\n";
        return std::move(*this) += rhs;
    }
#endif
};

int Int::cnt = 0;

int main()
{
    {
        std::cout << "test 1 - temporaries\n";
        Int x = Int(11) + Int(12) + Int(13) + Int(14) + Int(15) + Int(16);
        std::cout << "result: " << x.n() << "\n";
    }
    std::cout << "Number of constructions/destructions: " << Int::cnt << "\n\n";
    Int::cnt = 0;

    {
        std::cout << "test 2 - variables\n";
        Int a(31);
        Int b(32);
        Int c(33);
        Int d(34);
        Int e(35);
        Int f(36);
        Int x = a + b + c + d + e + f;
        std::cout << "result: " << x.n() << "\n";
    }
    std::cout << "Number of constructions/destructions: " << Int::cnt << "\n\n";
}