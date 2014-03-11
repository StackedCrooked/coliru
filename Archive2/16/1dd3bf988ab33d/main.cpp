#include <map>
#include <iostream>
#include <string>

int main() {
    std::map<std::string,std::string> toto { {"nom","robert"},{"prenom","petit"} };
    toto["age"] = "capitaine";
    
    for( auto & pair : toto )
        std::cout << pair.first << " = " << pair.second << "\n";
    
    std::cout << "Par un find sur nom = " << toto["nom"] << std::endl;
}