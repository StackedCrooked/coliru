#include <iostream>
#include <cstring>
using namespace std;

class Students {
    char names[10];
    char gender[10];
    char subjects[10];
    int ages;
    int highestMark;
    int lowestMark;
    void reset()
    {
      strncpy(names, "NULL", sizeof(names));
      names[9] = '\0';
      ages = 0;
      highestMark = 0;
      lowestMark = 0;
      strncpy(gender, "NULL", sizeof(gender));
      gender[9] = '\0';
      strncpy(subjects, "NULL", sizeof(subjects));
      subjects[9] = '\0';
    }
public:
    Students()
    {
      reset();
    }
    Students(const Students& student)
    {
       reset();
       cout << highestMark << endl; // PRINTS 107894124
       cout << lowestMark << endl;  // PRINTS 541203654
       cout << ages << endl; // PRINTS RANDOM VALUES
       cout << subjects << endl;
       cout << names << endl;
    }
};

int main( int, char** )
{
    Students s1;
    Students s2(s1);
    return( 0 );
}
