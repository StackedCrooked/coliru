#include <iostream>
#include <iomanip>
using namespace std;

class Person {

    public:

        enum Gender { MALE, FEMALE };

        Person(string name, int age, Gender gender) : name(name), age(age), gender(gender) { }

    // Getters
    string getName();
    int getAge();
    Gender getGender();

    protected:

        string name;
        int age;
        Gender gender;

};

// Getters
string Person::getName()
{
    return name;
}

int Person::getAge()
{
    return age;
}

Person::Gender Person::getGender()
{
    return gender;
}

class Student : public Person {

    public:

    Student(string name, int age, Gender gender, int id) : Person(name, age, gender), id(id) { }

    // Getters
    int getId();

    protected:

        int id;

};

int Student::getId()
{
    return id;
}

int main() {
    Student student("Cody Smith", 42, Student::MALE, 1234);

cout << std::setw(15) << std::left << "Name"
             << std::setw(10) << std::left << "Age"
             << std::setw(10) << std::left << "Gender"
             << std::setw(10) << std::left << "ID"
             << endl;

        char gender = 'M';
        if(student.getGender() == Person::FEMALE)
            gender = 'F';

        cout << std::setw(15) << std::left << student.getName()
             << std::setw(10) << std::left << student.getAge()
             << std::setw(10) << std::left << gender
             << std::setw(10) << std::left << student.getId()
             << endl << endl;
}