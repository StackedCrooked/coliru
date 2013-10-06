#include <string>
#include <iostream>
#include <vector>
#include <array>

#define NO_OF_TEST 3

using namespace std;

struct studentType
{
    string studentID;
    string firstName;
    string lastName;
    string subjectName;
    string courseGrade;

    array<unsigned, NO_OF_TEST> arrayMarks;
};

studentType input();

int main()
{
    vector<studentType> vec;
    studentType s;
    char response;

    do
    {
        cout << "\nEnter y to continue or q to quit... ";
        cin >> response;
        if (response == 'y')
        {
            vec.push_back(input());
        }

        else if (response == 'q')
        {
            for (unsigned int y=0; y<vec.size(); y++)
            {
                cout << "\nFirst name:   " << vec[y].firstName;
                cout << "\nLast name:    " << vec[y].lastName;
                cout << "\nStudent ID:   " << vec[y].studentID;
                cout << "\nSubject name: " << vec[y].subjectName;
            }
        }
    }
    while(response!='q');
}

studentType input()
{   
    studentType newStudent;

    cout << "\nPlease enter student information:\n";
    cout << "\nFirst Name: ";
    cin >> newStudent.firstName;
    cout << "\nLast Name: ";
    cin >> newStudent.lastName;
    cout << "\nStudent ID: ";
    cin >> newStudent.studentID;
    cout << "\nSubject Name: ";
    cin >> newStudent.subjectName;
    for (int x=0; x<NO_OF_TEST; x++)
    {   cout << "\nTest " << x+1 << " mark: ";
        cin >> newStudent.arrayMarks[x];
    }

    if (!cin) 
        throw "Invalid input";

    return newStudent;
}
