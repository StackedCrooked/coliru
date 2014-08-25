#include <iostream>
 
class Int
{
    int n_;
 
public:
    explicit Int(int n) noexcept : n_(n) { std::cout << "Int(" << n_ << ")\n"; }
 
    Int(Int && rhs)      : n_(rhs.n_) { std::cout << "Int(Int &&)     [" << n_ << "]\n"; }
 
    ~Int() { std::cout << "~Int()[" << n_ << "]\n"; }
 
    Int&& operator+=(Int&& rhs) && { 
        n_ += rhs.n_; 
        return std::move(*this); 
        }
 
    Int&& operator+(Int&& rhs) && { 
        std::cout << "Int operator+( Int&& rhs)&& (" << n_ << " " << rhs.n_ <<")\n";
        return std::move(*this) += std::move(rhs);
    }
};
 
 
int main()
{
    Int x = Int(11) + Int(12) + Int(13);
}