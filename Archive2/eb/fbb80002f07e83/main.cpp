#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

class student {
public:
    student(std::string student_name, int student_age)
        : name(student_name), age(student_age) { }

    std::string describe() const {
        return name + " is " + std::to_string(age) + " years old!\n";
    }

private:
    std::string name;
    int age;
};

std::ostream& operator<<(std::ostream& stream, student const& st) {
    stream << st.describe();
    return stream;
}

int main() {
    std::vector<student> students{student("Thomas", 18), student("Radek", 19)};
    std::copy(students.begin(), students.end(), std::ostream_iterator<student>(std::cout));
    return 0;
}
