#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/regex.hpp>

namespace sed {

enum SedModifier {
    g = 1,
    i = 2,
    gi = 3, ig = 3,
    d = 4,
    di = 6, id = 6,
};

struct Sed {
    boost::regex search;
    std::string replace;
    int mods;
};

struct SedProxy {
    SedProxy &operator/(const std::string &str) {
        if (!replace_) {
            sed_.search = str;
            sed_.replace.clear();
            sed_.mods = 0;
        } else sed_.replace = str;

        replace_ = !replace_;
        return *this;
    }

    SedProxy &operator/(SedModifier mod) {
        if (mod & d) {
            sed_.search = "[^\\n]*?" + sed_.search.str() + ".*?$";
        }

        if (mod & i) sed_.search.assign(sed_.search.str(), boost::regex_constants::icase);

        sed_.mods |= mod;
        replace_ = false;
        return *this;
    }

    Sed operator~() const {
        return sed_;
    }

private:
    Sed sed_;
    bool replace_{};
} s;

struct String {
    String(std::string str) : str_{std::move(str)} {}

    operator std::string() const {
        return str_;
    }

    String &operator=(const Sed &sed) {
        if (sed.search.empty()) throw std::logic_error("Bad substitution");

        auto flags = boost::format_first_only;
        if ((sed.mods & g) || (sed.mods & d)) flags = boost::format_default;

        str_ = boost::regex_replace(str_, sed.search, sed.replace, flags);
        return *this;
    }

private:
    std::string str_;
};

std::ostream &operator<<(std::ostream &out, const String &str) {
    return out << static_cast<std::string>(str);
}

} //sed namespace

int main() {
    using namespace sed;

    String str("bAnanAs");
    str =~ (s/"[an]"/"."/gi); //b.....s
    std::cout << str;
}