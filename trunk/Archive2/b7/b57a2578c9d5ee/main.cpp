#include <iostream>

#include <string> 

class GradeBook
{
public:
    explicit GradeBook(std::string);
    void setCourseName(std::string);
    std::string getCourseName() const;
    void displayMessage()const;
    void setInstructorName(std::string);
    std::string getInstructorName() const;
private:
    std::string courseName;
    std::string instructorName;  
};

using namespace std;

GradeBook::GradeBook(string name): courseName(name)

{

}

void GradeBook::setCourseName() const
{
    courseName = name;
}

string GradeBook::getCourseName() const 
{
    return courseName;
}

void GradeBook::setInstructorName() const
{
    instructorName = name;
}

string GradeBook::getInstructorName() const
{
    return instructorName;
}
void GradeBook::displayMessage() const
{
    cout << "Welcome to the grade book for\n" << getCourseName() << "with"     << getInstructorName << "!" << endl;
}

int main()
{
    GradeBook courseName("COP2224: Intro To C++ Programming");
    GradeBook instructorName("Heidi Gentry Kolen");
}                                                  
