class String
{
public:
String();
String(char Character);
String(char * CharacterString);
~String();
String(const String & copy);
String & operator = (const String & rhs);
char * GetString (String CString);
void Test();
void Display();

private:
char m_SingleChar;
char * m_CString;
};

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

String::String() :m_SingleChar('\0'), m_CString(nullptr)
{ }

String::String(char Character) : m_SingleChar(Character)
{ }

String::String(char * CharacterString)
{
if (CharacterString != nullptr)
{
    m_CString = new char [strlen(CharacterString) + 1];
    strcpy (m_CString, CharacterString);
}
}

String::~String()
{
delete [] m_CString;
}

String::String(const String & copy) : m_SingleChar(copy.m_SingleChar)
{
if (copy.m_CString != nullptr)
{
    m_CString = new char [strlen(copy.m_CString) + 1];
    strcpy (m_CString, copy.m_CString);
}
}

String & String::operator = (const String & rhs)
{
if (this != &rhs)
{
    delete [] m_CString;
    if(rhs.m_CString == nullptr)
        m_CString = nullptr;
    else
    {
        m_CString = new char[strlen(rhs.m_CString) + 1];
        strcpy (m_CString, rhs.m_CString);
    }
    m_SingleChar = rhs.m_SingleChar;
}
return *this;
}

char * String::GetString(String m_CString)
{
char * Cstring = m_CString.m_CString;
return Cstring;
}

void String::Test()
{

}

void String::Display()
{
cout << "Single character: " << m_SingleChar << endl;
cout << "C String:  " << m_CString << endl;
}

int main() {
    String s;
    s.Test();
}