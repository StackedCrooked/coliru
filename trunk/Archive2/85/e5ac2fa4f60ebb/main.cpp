#include <iostream>
#include <string.h>

using namespace std;
const int arr_size = 3;

char person_names[arr_size][20]={"Liz","Ann","Peter"};
int person_ages[arr_size]={19,22,20};

struct person
{
    char name[20];
    int age;
};

int main ()
{
    person parr[arr_size];
    for (int i=0; i<arr_size; i++)
    {
        strcpy (parr[i].name, person_names[i]);
        parr[i].age = person_ages[i];
    };

for (int i=0; i<arr_size; i++)
{
    cout << parr[i].name << " " << parr[i].age << endl;
};
return 0;
}