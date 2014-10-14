#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    std::fstream ifInput("aaa.txt");
    if (ifInput.fail())
    {
       cerr << "couldn't read file " ;
        return 1;
    }

    std::fstream* m_Stream = &ifInput;

    cout << m_Stream->tellg() << endl;
   // Res = 0;
    char cBuffer[4];
    m_Stream->read(&cBuffer[0], 4); 
    if (m_Stream->fail())
        return 1;

    cout << m_Stream->tellg() << endl;
    return 0;
}