class bin_tree
{
private:
    int data[4];

public:
    int getData(int)
    {
        return 1;
    };
    bin_tree()
        : data{1, 2, 3, 4}
    {
        // or:
        data[0] = 11;
        data[1] = 22;
        // ...
    };
};

#include <iostream>
int main()
{
    bin_tree tr;
    std::cout << "OK";
}