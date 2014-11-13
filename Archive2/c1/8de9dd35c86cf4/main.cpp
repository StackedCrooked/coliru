#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Pointer
{
public:
    Pointer() {}
    ~Pointer() {}

    void printSomething()
    {
        std::cout << "Hi" << std::endl;
    }
};

class Keeper
{
public:
    typedef std::vector<std::unique_ptr<Pointer>> vector_type;

    Keeper() {}
    virtual ~Keeper() {}

    void push_back(vector_type::value_type && pointer)
    {
        data.push_back(std::move(pointer));
    }

    auto begin() const
    {
        return data.begin();
    }

    auto end() const
    {
        return data.end();
    }
private:
    vector_type data;
};

int main()
{
    Keeper keeper;
    keeper.push_back(std::make_unique<Pointer>());

    std::for_each(keeper.begin(), keeper.end(), [] (auto && pointer) {
        pointer->printSomething();
    });
}