#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Student {
 public: 
  string last;
  string first;
  int student_id;
  
  friend std::istream& operator>>(std::istream& in, Student&);
  friend std::ostream& operator<<(std::ostream& out, const Student&);
};

class Course {
 public:
  string name;
  int course_id;
  vector <Student> students;
  
  friend std::istream& operator>>(std::istream& in, Course&);
  friend std::ostream& operator<<(std::ostream& out, const Course&);
};

class Gradebook {
 public:
  Gradebook() {}
  void addCourse() {}
  void addStudent(){} 
 private:
  vector <Course> courses;
  
  friend std::istream& operator>>(std::istream& in, Gradebook&);
  friend std::ostream& operator<<(std::ostream& out, const Gradebook&);
};









std::istream& operator>>(std::istream& in, Student& newEntry)
{
    in>>newEntry.student_id;
    in>>newEntry.last;
    in>>newEntry.first;
    return in;
}
std::ostream& operator<<(std::ostream& out, const Student& Entry)
{
    out<<Entry.student_id<<' ';
    out<<Entry.last<<' ';
    out<<Entry.first;
    return out;
}
std::istream& operator>>(std::istream& in, Course& newEntry)
{
    in>>newEntry.course_id;
    in>>newEntry.name;
    
    int number_of_students;
    in >> number_of_students;
    for(int i=0; in && i<number_of_students; ++i) {
        Student newStudent;
        in >> newStudent;
        newEntry.students.push_back(newStudent);
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const Course& Entry)
{
    out<<Entry.course_id<<' ';
    out<<Entry.name<<' ';
    out<<Entry.students.size() << ' ';
    for(int i=0; i<Entry.students.size(); ++i) {
        out << Entry.students[i] << ' ';
    }
    return out;
}
std::istream& operator>>(std::istream& in, Gradebook& newEntry)
{
    int number_of_courses;
    in >> number_of_courses;
    for(int i=0; in && i<number_of_courses; ++i) {
        Course newCourse;
        in >> newCourse;
        newEntry.courses.push_back(newCourse);
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const Gradebook& Entry)
{
    out<<Entry.courses.size() << ' ';
    for(int i=0; i<Entry.courses.size(); ++i) {
        out << Entry.courses[i] << ' ';
    }
    return out;
}





#include <fstream>

int main() {
    Gradebook grades;
    
    {
        std::ifstream inputFile("file.txt");
        inputFile >> grades;
    }
    
    std::cout << grades;
    
    {
        std::ofstream outputFile("results.txt");
        outputFile << grades;
    }
}