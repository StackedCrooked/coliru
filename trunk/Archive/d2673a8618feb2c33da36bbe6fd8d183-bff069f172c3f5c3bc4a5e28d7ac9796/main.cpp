struct date {
private:
    unsigned month_ = 1;
    unsigned day_ = 1;
    int year_ = 1970;

    constexpr int modified_year() noexcept {
        return year_ - (month_ <= 2);
    }

    constexpr int era() noexcept {
        return (modified_year() >= 0 ? modified_year() : modified_year() - 399) / 400;
    }

    constexpr unsigned year_of_era(unsigned era) noexcept {
        return modified_year() - era * 400; // [0, 399]
    }

    constexpr unsigned day_of_era(unsigned era) noexcept {
        return year_of_era(era) * 365 + year_of_era(era) / 4 - year_of_era(era) / 100 + day_of_year(); // [0, 146096]
    }

public:
    constexpr date() = default;
    constexpr date(unsigned m, unsigned d, int y) noexcept: month_(m), day_(d), year_(y) {}

    constexpr unsigned day_of_year() noexcept {
        return (153 * (month_ + (month_ > 2 ? -3 : 9)) + 2)/5 + day_ - 1; // [0, 365]
    }

    constexpr int days_since_unix_time() noexcept {
        return era() * 146097 + static_cast<int>(day_of_era(era())) - 719468;
    }
};

#include <iostream>

int main() {
    constexpr date d = { 8, 24, 2013 };
    static_assert(d.days_since_unix_time() == 15941, "..");
}