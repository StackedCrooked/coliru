#include <map>
#include <vector>
#include <functional>
#include <iostream>

void do_sum() {
    std::cout << "TODO: do_sum\n";
}

void do_average() {
    std::cout << "TODO: do_average\n";
}

int main(int argc_, char const** argv_) {
    std::vector<std::string> const args(argv_+1, argv_+argc_);

    static std::map<std::string, std::function<void()> > const functions {
        { "sum", do_sum },
        { "average", do_average },
    };

    for (auto& arg : args) {
        auto entry = functions.find(arg);
        if (entry == functions.end()) {
            std::cerr << "Function '" << arg << "' not implemented\n";
        } else
        {
            entry->second();
        }
    }
}
