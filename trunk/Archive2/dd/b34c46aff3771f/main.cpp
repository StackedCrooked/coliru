#include <memory>
#include <vector> 
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <set>

class Person {
    public:
    std::string firstname() const; //default init 
    std::string lastname() const; // default init
};

class PersonSortCriterion {
    public:
    bool operator() (const Person& p1, const Person& p2) const {
        // a person is less than another person
        //- if the last name is less
        //- if the last name is equal and the first name is less
        return p1.lastname() < p2.lastname() || 
        (p1.lastname() == p2.lastname() && p1.firstname() < p2.firstname() );
    }
};



int main()
{
    
    set<Person, PersonSortCriterion> coll;
    
    
    
    return 0; 
}
    
    
