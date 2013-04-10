#include <iostream>
#include <map>
#include <sstream>

struct person_type {
    std::string key1;
    std::string name1;
    std::string address1;
};
std::istream& operator>>(std::istream& in, person_type& p)
{
    std::getline(in, p.key1,  ':');
    std::getline(in, p.name1,':');
    return std::getline(in, p.address1);
}
std::ostream& operator<<(std::ostream& out, const person_type& p)
{
    return out << p.key1 << ':' << p.name1 << ':' << p.address1 << '\n';
}
 
int main() {
    std::map<std::string, person_type> PNTree;
    
    std::istringstream dataFile;
    dataFile.str( 
        "33324532434:Ryan:77 Easy Street\n"
        "332453212346:Tom:1 Victory Lane\n"
        "33268547:Gary:69 Sexual Ave\n"
        "330435742:Susan:11 Straight Road\n"
        "33436511234:Frank:96 Backwards street\n");
    
    person_type temp;
    while(dataFile >> temp)
        PNTree[temp.key1] = std::move(temp);
    
    for(auto it=PNTree.begin(); it!=PNTree.end(); ++it)
        std::cout << it->second;
}


