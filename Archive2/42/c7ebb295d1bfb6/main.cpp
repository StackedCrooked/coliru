#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argc);
    std::copy(argv, argv + argc, args.begin());
    for (const auto& s : args)
        std::cout << s << '\n';
}