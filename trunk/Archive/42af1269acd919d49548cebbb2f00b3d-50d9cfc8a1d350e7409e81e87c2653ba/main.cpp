#include <iostream>
#include <map>
#include <sstream>

struct person_type {
    std::string key1;
    std::string name1;
    std::string address1;
};
 
int main() {
    std::map<std::string, person_type> PNTree;
    person_type person[5];
    std::istringstream dataFile;
    dataFile.str( 
        "33324532434:Ryan:77 Easy Street\n"
        "332453212346:Tom:1 Victory Lane\n"
        "33268547:Gary:69 Sexual Ave\n"
        "330435742:Susan:11 Straight Road\n"
        "33436511234:Frank:96 Backwards street\n");
    //ifstream dataFile;
    //dataFile.open ("/Users/revaes12/Desktop/BinarySearch/BinarySearch/phone.dat.rtf");
    
    for (int counter = 0; counter < 5; counter++)
    {
        getline(dataFile, person[counter].key1,  ':');
        getline(dataFile, person[counter].name1,':');
        getline(dataFile, person[counter].address1);
        PNTree[person[counter].key1] =  person[counter];
    }
    //dataFile.close();
}


