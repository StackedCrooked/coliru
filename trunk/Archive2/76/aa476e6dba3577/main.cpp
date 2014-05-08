#include <string>

template<class T>
void func(T&&) {}

int main() {
    const char* t = "HI";
    func<std::string>(static_cast<const char*>(t));
    func<std::string>(static_cast<const char*&>(t));
    func<std::string>(static_cast<const char*&&>(t));
    func<std::string>(static_cast<const char*const>(t));
    func<std::string>(static_cast<const char*const&>(t));
    func<std::string>(static_cast<const char*const&&>(t));
}