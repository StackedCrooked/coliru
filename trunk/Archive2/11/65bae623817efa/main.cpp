#include <iostream> // cout
#include <iterator> // begin/end

int main()
{
    int arr[] = { 1, 2, 3, 4, };
    for (auto elem : arr)
        std::cout << elem << ",";
}
