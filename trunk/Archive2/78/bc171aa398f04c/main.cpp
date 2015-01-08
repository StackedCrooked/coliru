#include <string>
class StringTool
{

public:

StringTool(std::string name);
StringTool(StringTool const& other);
~StringTool();
void Print();
std::string getName();
void setName(std::string name);

private:

std::string name;
};

#include <iostream>
#include <string>

using namespace std;

StringTool::StringTool(std::string name)
{
    this->name = name;
    cout<<"Construct: "<<name<<endl;
}

StringTool::StringTool(StringTool const& other)
: name(other.name)
{
    cout<<"Copy: "<<name<<endl;
}

StringTool::~StringTool()
{
    cout<<"Delete: "<<name<<endl;
}

void StringTool::Print()
{
    cout<<"Print: "<<name<<endl;
}

int main() {

    StringTool tool = StringTool("Test");
    tool.Print();

    tool = StringTool("New Test");
    tool.Print();
}