#include <iostream>
#include <random>
#include <string>
#include <vector>


std::vector<std::string> names = {
    "Ellen",
    "Anne",
    "Hoogvliet",
    "Adam",
    "Gaycopper",
    "Firegay",
    "Birthday suit",
    "Rob",
    "Anne Bor",
    "Ad Frank",
    "JANEIN",
    "SCHILSSPASS",
    "Krauth",
    "Schildkat",
    "Shieldput",
    "Alfriet Krauth",
    "Kater Krauth",
    "Arthur Krauth",
    "Elfriede Jeeedelooooooh",
    "LOLLEON",
    "Pim",
    "Arthur Sillen Krauth",
    "Pop Kek",
    "Topkak",
    "Kutkat",
    "Topkakat",
    "Pokekat",
    "LELTHISCATLIVESLONGERTHENIWILLDO"
};


int main()  
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, names.size());
    
    std::cout << names[dis(gen)] << std::endl;
}