#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using namespace std;

class Husband{
    friend void change_salary(int changed_salary, Husband &ob);

public:
    Husband() {}
    Husband(int new_salary) : salary{ new_salary } {}

private:
    int salary;

};

void change_salary(int changed_salary, Husband &ob);  //<----Code Compiles without even this declaration

#endif

//#include "test.hpp"

int main()
{
    Husband hs1{ 3000 };

    change_salary(4000, hs1);  // <---- Able to use function without explicit declaration outside of class in header

    void (*p)(int, Husband&) = &change_salary;
    return 0; 
}

//#include "test.hpp"

void change_salary(int changed_salary, Husband &ob)
{
    cout << "salary increased by 1000\n";
    ob.salary = changed_salary;
}
