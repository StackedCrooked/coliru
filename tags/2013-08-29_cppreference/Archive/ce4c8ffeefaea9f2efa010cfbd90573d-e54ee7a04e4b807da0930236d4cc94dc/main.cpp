#include <iostream>
#include <string>

std::string basename(const std::string& path)
{
    return path.substr(path.rfind('/') + 1);
}

void test(const std::string& path)
{
    std::cout << "'" << path << "' => '" << basename(path) << "'\n";
}


int main()
{
    test("test");
    test("./test");
    test("./bin/test");
    test("/bin/test");
    test("/");
    test("/test/");
}