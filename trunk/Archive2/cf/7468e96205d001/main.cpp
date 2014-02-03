#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class Student
{
public:
    void InputData(std::string, const std::vector<std::string>&);
    void OutputData();
    void ResetClasses();
private:
    std::string name;
    std::vector<std::string> classList;
};

void Student::InputData(std::string nm, const std::vector<std::string>& names)
{
    name = nm;
    classList = names;
}

void Student::OutputData()
{
    std::cout << "Students name: " << name << std::endl;
    std::cout << "Classes: ";
    
    std::copy(classList.begin(), classList.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}

void Student::ResetClasses()
{
    name.clear();
    classList.clear();
}

int main()
{
    
}