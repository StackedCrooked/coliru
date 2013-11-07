#include <iostream>
#include <functional>
#include <vector>
#include <tuple>
#include <type_traits>

template <typename... Args>
class Shibe {
    public:
        Shibe() { 
            std::vector<std::string> pack({Args()...});
            for (const auto& peck : pack) {
                std::cout << peck << std::endl;
            }
        }
        ~Shibe() { }
        
        template <typename... args>
        void is(args... a) {
            std::vector<std::string> pack({a...});
            for (const auto& peck : pack) {
                std::cout << peck << std::endl;
            }
        }
};

class wow {
    public:
        wow() { }
        ~wow() { }
        operator std::string() const {
            return std::string("wow");
        }
};

class such {
    public:
        such() { }
        ~such() { }
        operator std::string() const {
            return std::string("such");
        }
};

class amazing {
    public:
        amazing() { }
        ~amazing() { }
        operator std::string() const {
            return std::string("amazing");
        }
};

class bow_wow {
    public:
        bow_wow() { }
        ~bow_wow() { }
        operator std::string() const {
            return std::string("bow wow");
        }
};

template <typename T>
class red_alert {
    public:
        template <typename... Args>
        red_alert(Args... a) { 
            std::vector<T> pack({a...});
            for (const auto& peck : pack)
                std::cout << peck << std::endl;
        }
        ~red_alert() { }
        
        operator std::string() const {
            return std::string("red alert");
        }
};

int main(int argc, char* argv[]) {
    Shibe<wow, such, amazing> doge;
    doge.is(bow_wow(), red_alert<std::string>("don't touch", "will bite"));
    return 0;
}
