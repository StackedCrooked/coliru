#include <limits>
#include <utility>

template<typename T, T min = std::numeric_limits<T>::min(), 
                     T max = std::numeric_limits<T>::max()>
struct ranged_value {
private:
    T value;
public:
    constexpr ranged_value() = default;
    constexpr ranged_value(T v): value(std::move(v)) {}
    constexpr T get() const noexcept(noexcept(value > max) && noexcept(value < min)) {
        return value > max ? max : value < min ? min : value;
    }
    
    constexpr operator T() const {
        return get();
    }
    
    ranged_value& operator+=(const ranged_value& x) {
        value = get() + x.get();
        return *this;
    }
    
    ranged_value& operator-=(const ranged_value& x) {
        value = get() - x.get();
        return *this;
    }
    
    ranged_value& operator*=(const ranged_value& x) {
        value = get() * x.get();
        return *this;
    }
    
    ranged_value& operator/=(const ranged_value& x) {
        value = get() / x.get();
        return *this;
    }
    
    ranged_value& operator%=(const ranged_value& x) {
        value = get() % x.get();
        return *this;
    }
    
    ranged_value& operator&=(const ranged_value& x) {
        value = get() & x.get();
        return *this;
    }
    
    ranged_value& operator^=(const ranged_value& x) {
        value = get() ^ x.get();
        return *this;
    }
    
    ranged_value& operator<<=(const ranged_value& x) {
        value = get() << x.get();
        return *this;
    }
    
    ranged_value& operator>>=(const ranged_value& x) {
        value = get() >> x.get();
        return *this;
    }
    
    ranged_value& operator|=(const ranged_value& x) {
        value = get() | x.get();
        return *this;
    }
    
    ranged_value& operator++() {
        value = get() + 1;
        return *this;
    }
    
    ranged_value& operator--() {
        value = get() - 1;
        return *this;
    }
    
    ranged_value operator++(int) {
        ranged_value copy = *this;
        ++(*this);
        return copy;
    }
    
    ranged_value operator--(int) {
        ranged_value copy = *this;
        --(*this);
        return copy;
    }
};

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator+(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() + rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator-(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() - rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator*(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() * rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator/(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() / rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator%(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() % rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator<<(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() << rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator>>(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() >> rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator&(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() & rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator|(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() | rhs.get() };
}

template<typename T, T min, T max>
constexpr ranged_value<T, min, max> operator^(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return { lhs.get() ^ rhs.get() };
}

template<typename T, T min, T max>
constexpr bool operator==(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return lhs.get() == rhs.get();
}

template<typename T, T min, T max>
constexpr bool operator!=(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return lhs.get() != rhs.get();
}

template<typename T, T min, T max>
constexpr bool operator<(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return lhs.get() < rhs.get();
}

template<typename T, T min, T max>
constexpr bool operator>(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return lhs.get() > rhs.get();
}

template<typename T, T min, T max>
constexpr bool operator>=(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return lhs.get() >= rhs.get();
}

template<typename T, T min, T max>
constexpr bool operator<=(const ranged_value<T, min, max>& lhs, const ranged_value<T, min, max>& rhs) {
    return lhs.get() <= rhs.get();
}

#include <iostream>

int main() {
    ranged_value<int, 0, 100> x(-34);
    x = (x + 1) * 200;
    if(x == 100) {
        std::cout << "...";
    }
}
