#include <array>
#include <cstddef>
#include <stdexcept>

template<typename CharT, std::size_t N>
class basic_fixed_string {
public:
    using size_type = decltype(N);

    fixed_string() : size_(0) { }

    CharT& operator[](size_type index) {
        return at(index);
    }

    CharT const& operator[](size_type index) const {
        return at(index);
    }

    CharT& at(size_type index) {
        if (index >= size_) {
            throw std::out_of_range(__function__);
        }
        return data_[index];
    }

    CharT const& at(size_type index) const {
        return const_cast<fixed_string&>(*this).at(index);
    }

private:
    std::array<CharT, N> data_;
    size_type size_;

    friend bool operator==(fixed_string const& a, fixed_string const& b) {
        return a.data_ == b.data_;
    }

    friend bool operator!=(fixed_string const& a, fixed_string const& b) {
        return a.data_ != b.data_;
    }

    friend bool operator>=(fixed_string const& a, fixed_string const& b) {
        return a.data_ >= b.data_;
    }

    friend bool operator<=(fixed_string const& a, fixed_string const& b) {
        return a.data_ <= b.data_;
    }

    friend bool operator>(fixed_string const& a, fixed_string const& b) {
        return a.data_ > b.data_;
    }

    friend bool operator<(fixed_string const& a, fixed_string const& b) {
        return a.data_ < b.data_;
    }
};

template<std::size_t N>
using fixed_string = basic_fixed_string<char, N>;
