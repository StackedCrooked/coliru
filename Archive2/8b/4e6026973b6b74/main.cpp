#include <iostream>
#include <istream>
#include <string>

struct course_record { 
    std::string course; 
    int mark;
};

struct student_record { 
    std::string name; /* name of student */
    course_record course[5]; /* courses taken by student */
}test[2];

void read_record (student_record &str) {
    std::string line;
    std::getline(std::cin, line);
    size_t pos = line.find('%');
    
    str.name = line.substr(0, pos);
    size_t prev;
    
    for (auto &c : str.course) {
        prev = pos;
        pos = line.find('%', pos + 1);
        c.course = line.substr(prev + 1, pos - prev - 1);
        prev = pos;
        pos = line.find('%', prev + 1);
        c.mark = std::stoi(line.substr(prev + 1, pos - prev - 1));
    }
}

void write_record (const student_record &str) {
    std::cout << "Student name: " << str.name << std::endl;
    
    for (auto &c : str.course) {
        std::cout << c.course << " -> " << c.mark << std::endl;
    }
}

int main()
{
    for (auto &rec : test) {
        read_record(rec);
        write_record(rec);
        std::cout << std::endl;
    }
    return 0;
}