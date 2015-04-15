#include <iostream>
#include <string>
#include <type_traits>

void splitPath(const std::string& path, std::string& outDir, std::string& outFile)
{
    std::size_t sep = path.find_last_of("/\\");
    outDir = path.substr(0, sep > 1 ? sep : 1);
    outFile = path.substr(sep + 1);
}

void test(const std::string& path)
{
    std::string dir, file;
    splitPath(path, dir, file);

    std::cout << "Split \"" << path << "\"\n";
    std::cout << "    dir  = " << dir << "\n";
    std::cout << "    file = " << file << "\n";
}

int main()
{
    test("/");
    test("/var/log/test.log");
    test("C:\\Documents and Settings\\My Music\\Super Song.mp3");
}