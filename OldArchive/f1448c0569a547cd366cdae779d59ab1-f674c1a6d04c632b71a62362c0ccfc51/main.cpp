#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char** argv) {
    std::vector<std::string> args(argv,argv+argc);
    auto condition = [](const std::string& arg)->bool {return arg=="--item";};
    args.erase(std::remove_if(args.begin(), args.end(), condition), args.end());
}