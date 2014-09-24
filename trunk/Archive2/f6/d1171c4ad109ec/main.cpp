#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Person{
    string name;
    int age;
};

std::list<Person> list;

void append(std::list<Person>& list, const string& name, int age)
{
    list.push_back({name, age});
}

int main(){
    append( list, "First_Person", 21);
    append( list, "Second_Person", 22);
    //testing the result
    for (auto &person: list)
        cout << "name: " << person.name << endl;
    return 0;
}