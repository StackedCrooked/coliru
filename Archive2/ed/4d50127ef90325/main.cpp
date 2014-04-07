#include <iostream>
#include <istream>
#include <string>
#include <sstream>

struct course_record { std::string course;  int mark; }; 
struct student_record { 
    std::string name; // name of student 
    course_record course[5]; //courses taken by student
}test[2];

std::istream &operator >> (std::istream &iss, student_record &str) {
    std::string line;
    std::getline(iss, line);
    
    std::istringstream ss(line);
    std::getline(ss, str.name, '%');
    
    for (auto &c : str.course) {
        std::getline(ss, c.course, '%');
        ss >> c.mark;
        ss.get();
    }
    
    return iss;
}

std::ostream &operator << (std::ostream &oss, const student_record &str) {
    oss << "Student name: " << str.name << std::endl;
    
    for (auto &c : str.course) {
        oss << c.course << " -> " << c.mark << std::endl;
    }
    
    return oss;
}

int main()
{
    for (auto &rec : test) {
        std::cin >> rec;
        std::cout << rec << std::endl;
    }
    return 0;
}