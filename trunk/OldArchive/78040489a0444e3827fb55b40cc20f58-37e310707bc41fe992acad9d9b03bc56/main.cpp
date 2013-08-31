#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student{
    Student(unsigned int r) : roll(r), name(), course() {}
    unsigned int roll;
    string name;
    string course;
};

int main(){
    vector<Student> students;
    //populate the vector with meaningful data, here only roll is written
    for(unsigned int i = 0; i < 100; i++)
        students.push_back(Student(i));
    
    unsigned int min = 45;
    unsigned int max = 85;
    auto operation = [=](const Student& e){if( (e.roll >= min) and (e.roll <= max) ) cout << e.roll << endl;};
    for_each(students.begin(), students.end(), operation);
}
