#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <fstream>

using namespace std;

struct FileHelper
{
    static void write(const string& filePath, const function<void (ostream&)>& f)
    {
        ofstream file(filePath);
        f(file);
    }
    
    static void write(const string& filePath, const string& contents)
    {
        write(filePath, [&](ostream& s) { s.write(contents.c_str(), contents.size()); });
    }
};

struct StringHelper
{
    static string stream(const function<void (ostream&)>& f)
    {
        stringstream ss;
        f(ss);
        return ss.str();
    }
};

int main()
{
    int x = 42;
    
    FileHelper::write(
        "ninjas.txt",
        StringHelper::stream([&](ostream& s) { s << x; }));
}
