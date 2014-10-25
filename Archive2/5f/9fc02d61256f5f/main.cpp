#include <array>
#include <cstddef>
#include <cstring>
#include <stdexcept>

template<typename CharT, std::size_t N>
class basic_fixed_string {
public:
    using size_type = decltype(N);

    basic_fixed_string() : size_(0) { }

    basic_fixed_string(CharT const* c_string) : size_(std::strlen(c_string)) {
        if (size_ > N) {
            throw std::out_of_range(__func__);
        }
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = c_string[i];
        }
    }

    CharT* data() {
        return data_.data();
    }

    CharT const* data() const {
        return data_.data();
    }

    size_type size() const {
        return size_;
    }

    CharT& operator[](size_type index) {
        return at(index);
    }

    CharT const& operator[](size_type index) const {
        return at(index);
    }

    CharT& at(size_type index) {
        if (index >= size_) {
            throw std::out_of_range(__func__);
        }
        return data_[index];
    }

    CharT const& at(size_type index) const {
        return const_cast<basic_fixed_string&>(*this).at(index);
    }

    basic_fixed_string& operator+=(basic_fixed_string const& other) {
        if (size_ + other.size_ > N) {
            throw std::out_of_range(__func__);
        }
        std::copy(other.data_.begin(), other.data_.end(), data_.begin() + size_);
        return *this;
    }

private:
    std::array<CharT, N> data_;
    size_type size_;

    friend bool operator==(basic_fixed_string const& a, basic_fixed_string const& b) {
        return a.data_ == b.data_;
    }

    friend bool operator!=(basic_fixed_string const& a, basic_fixed_string const& b) {
        return a.data_ != b.data_;
    }

    friend bool operator>=(basic_fixed_string const& a, basic_fixed_string const& b) {
        return a.data_ >= b.data_;
    }

    friend bool operator<=(basic_fixed_string const& a, basic_fixed_string const& b) {
        return a.data_ <= b.data_;
    }

    friend bool operator>(basic_fixed_string const& a, basic_fixed_string const& b) {
        return a.data_ > b.data_;
    }

    friend bool operator<(basic_fixed_string const& a, basic_fixed_string const& b) {
        return a.data_ < b.data_;
    }

    friend basic_fixed_string operator+(basic_fixed_string a, basic_fixed_string const& b) {
        a += b;
        return a;
    }
};

template<std::size_t N>
using fixed_string = basic_fixed_string<char, N>;

#include <iostream>

int main() {
    fixed_string<42> hello("Hello, world!\n");
    std::cout << hello.data() << '\n';
    return 0;
}
