#include <iostream>
#include <string>
#include <vector>
#include <utility>

class VectorMoveDemo
{
public:
    void add(std::string item)
    {
        results_.push_back(item);
    }
    std::vector<std::string>& getVector()
    {
        return std::move(results_);
    }
private:
    std::vector<std::string> results_;
};

int main()
{
    VectorMoveDemo v;
    v.add("Hello ");

    std::cout << "First Time : " << "\n";
    std::vector<std::string> temp = v.getVector();
    for(auto &item : temp)
    {
        std::cout << item << "\n";
    }
    std::cout << "Second Time : " << "\n";

    v.add("World");

    std::vector<std::string> temp2 = v.getVector();
    for(auto &item : temp2)
    {
        std::cout << item << "\n";
    }
}
