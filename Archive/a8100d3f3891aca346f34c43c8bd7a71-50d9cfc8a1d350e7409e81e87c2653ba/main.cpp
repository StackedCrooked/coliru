#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

struct PersonInfo
{
    int age;
    std::string name;
    double height;
};

std::istream& operator>>(std::istream& inputFile, PersonInfo& newPerson) 
{return inputFile >> newPerson.age >> newPerson.name >> newPerson.height;}

std::ostream& operator<<(std::ostream& outputFile, const PersonInfo& newPerson) 
{return outputFile << newPerson.age << ' ' << newPerson.name << ' ' << newPerson.height;}

int main() {
    std::stringstream inputFile(
        "18 JIMMY 71.5\n"
        "32 TOM 68.25\n"
        "27 SARAH 61.4\n");
        
    typedef std::istream_iterator<PersonInfo> iit; //read in
    std::vector<PersonInfo> people{iit(inputFile), iit()}; 
    
    std::ostream_iterator<PersonInfo> oit(std::cout,"\n"); //write out
    std::copy(people.begin(), people.end(), oit);
    
    return 0;
}