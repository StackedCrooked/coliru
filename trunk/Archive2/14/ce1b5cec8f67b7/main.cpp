#include <string>
#include <iostream>

using namespace std;

int main()
{
    const char* filename = "file.txt";
    string fileNameStr{filename};
    auto dotPos = fileNameStr.find_last_of('.');
    auto fileName2 = fileNameStr.substr(0, fileNameStr.size()-dotPos);
    fileName2+="2.txt";
    cout << fileName2 << endl;
}
