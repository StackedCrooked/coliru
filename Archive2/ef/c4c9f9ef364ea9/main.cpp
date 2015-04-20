#include <iostream>
#include <cxxabi.h>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>

const std::string kBaseName("VICH");

void test(const std::string& iCryptic)
{
    std::cout << "=========== " << iCryptic << " ===========" << std::endl;
    try{
    std::cout << iCryptic.substr(
        iCryptic.find(kBaseName) + std::string(kBaseName).length() + 1,
        iCryptic.length()
    ) << std::endl;
    } catch (std::exception& iEx) {
        std::cout << "Uh ho ! " << iEx.what() << std::endl;
    }
}

int main()
{
    test("VICH");
    test("VICH?");
    test("VICH-k0");
}
