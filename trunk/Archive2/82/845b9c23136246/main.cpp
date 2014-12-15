#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
#include <tuple>

template <typename KeyType, typename Getter>
void one_function(KeyType& input,
                  Getter getter)
{
    std::cout << "inside one function " << getter(input) << std::endl;
}


int main() {
    auto aMap = std::unordered_map<std::string, std::pair<std::string, std::string> > { {"key1",{"value1_1","value1_2"} }, {"key2",{"value2_1","value2_2"}}};
    //using T = std::unordered_map<std::string, std::pair<std::string, std::string> >::mapped_type;

    std::get<1, std::string, std::string>(aMap.at("key1"));

    one_function(aMap["key1"], static_cast<std::string&(*)(std::pair<std::string, std::string>&)>(&std::get<1>));

    one_function(aMap["key1"], [](auto& p){ return std::get<1>(p); });
}
