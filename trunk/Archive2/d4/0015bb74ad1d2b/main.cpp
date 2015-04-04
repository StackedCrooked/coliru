#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>
#include <stdexcept>

struct big_token {
    std::string decimal;
    int64_t exponent = 0;
    bool positive = true;
};

namespace detail {
void handle_exponent(big_token& result, const std::string& str, size_t index) {
    if(index >= str.size()) {
        throw std::runtime_error("missing exponent after E or e");
    }

    bool negative = false;
    if(str[index] == '-') {
        negative = true;
        ++index;
    }
    else if(str[index] == '+') {
        ++index;
    }
    if(index >= str.size()) {
        throw std::runtime_error("missing exponent after sign");
    }

    int64_t exp = 0;
    for(; index < str.size(); ++index) {
        exp = (str[index] - '0') + exp * 10;
    }
    result.exponent += negative ? -exp : exp;
}

void handle_periods(big_token& result, const std::string& str, size_t index) {
    if(index >= str.size()) {
        return;
    }
    for(; index < str.size(); ++index) {
        if(str[index] == 'e' || str[index] == 'E') {
            handle_exponent(result, str, index + 1);
            return;
        }
        result.decimal.push_back(str[index]);
        --result.exponent;
    }
}
} // detail

big_token make_big_token(const std::string& str) {
    big_token result;
    size_t index = 0;
    const auto& size = str.size();
    if(str.front() == '+' || str.front() == '-') {
        ++index;
        result.positive = str.front() != '-';
    }

    // parse the decimal part
    for(; index < size; ++index) {
        if(str[index] == '.') {
            detail::handle_periods(result, str, index + 1);
            break;
        }
        else if(str[index] == 'e' || str[index] == 'E') {
            detail::handle_exponent(result, str, index + 1);
            break;
        }
        result.decimal.push_back(str[index]);
    }

    // normalise the exponent to the radix (10^9)
    auto imbalance = result.exponent % 9;
    size_t shift = 0;
    if(imbalance != 0) {
        if(result.exponent < 0) {
            shift = 9 + imbalance;
            result.exponent -= shift;
        }
        else {
            shift = 9 - imbalance;
            result.exponent += shift;
        }
        result.decimal.append(shift, '0');
    }
    return result;
}

#include <iostream>

struct decimal {
private:
    std::vector<uint32_t> mantissa;
    int64_t exponent = 0;
    bool positive = false;
public:
    static constexpr uint32_t base = 1000000000;
    static constexpr uint32_t digits10 = 9;
    decimal() = default;
    decimal(const std::string& str) {
        auto&& token = make_big_token(str);
        exponent = token.exponent / digits10;
        positive = token.positive;
        for(size_t i = token.decimal.size(); i != 0; ) {
            auto offset = i > digits10 ? i - digits10 : 0;
            auto length = offset == 0 ? i : digits10;
            mantissa.push_back(std::stoul(token.decimal.substr(offset, length)));
            i = offset;
        }
    }

    template<typename Stream>
    void print(Stream& out) {
        out << "decimal(positive=" << std::boolalpha << positive
            << ", exponent=" << exponent
            << ", mantissa={";

        char sep[] = { '\0', ' ', '\0' };
        for(auto&& elem : mantissa) {
            out << sep;
            out << elem;
            sep[0] = ',';
        }
        out << "})\n";
    }
};


int main() {
    decimal x("12345.6789123e-10");
    x.print(std::cout);
    decimal y("+123.4567");
    y.print(std::cout);
    decimal z("-123458912123.39812e+10");
    z.print(std::cout);
}
