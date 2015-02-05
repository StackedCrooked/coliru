#include <iostream>
#include <string>
#include <vector>
#include <memory>

std::vector<std::unique_ptr<int>* > blah;

int main()
{

    std::unique_ptr<int> ptr(new int()),

    blah.push_back(ptr);
}
