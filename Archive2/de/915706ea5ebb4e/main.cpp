#include <iostream>
#include <string>

struct StudentRecord {
    std::string Name;
    void printInfo() const {
        std::cout << "Name:" << Name << '\n';
    }
};

int main() {
    StudentRecord TESCStudent;
    TESCStudent.Name = "SuperProgrammer";
    TESCStudent.printInfo();
}