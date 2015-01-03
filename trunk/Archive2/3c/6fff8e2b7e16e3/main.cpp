#include <iostream>
#include <sstream>
using std::cout;
using std::string;
using std::endl;

std::stringstream dummy("david\n4\njohn\n35");

typedef struct
{
    int age;
    string name;
} people;

people* register_people( people* data, int n);

int main(void)
{
    people data[2];
    people* info[2];

    info[0] = register_people(data, 2);

    cout << "Name: " << info[0]->name
         << "\tAge: " << info[0]->age;
         
    /* BAD CODE -- ACCESSES info[1] WHICH IS AN UNINITIALIZED POINTER!!
    cout << "Name: " << info[1]->name
         << "\tAge: " << info[1]->age; */

    return 0;
}

people* register_people( people* data, int n)
{
    int i;

    for ( i = 0; i < n; i++ )
    {
        cout << "People" << i + 1 << ":" << endl;
        cout << "   " << "name: ";
        getline(dummy, data[i].name);

        cout << "   " << "age: ";
        dummy >> data[i].age;

        dummy.ignore();
    }
    return data;
}