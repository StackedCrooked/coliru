#include <iostream>
#include <string>
#include <vector>
#include <type_traits>


template <typename T, typename sepT = char>
void print2d(const T &data, sepT sep = ',') {
    static_assert(std::is_same<T, int[2][2]>::value, "Fail");
    static_assert(std::is_same<decltype(data), const int(&)[2][2]>::value, "Fail");
}

int main(){
    int arr[2][2] = {{1,2},{3,4}};
    print2d(arr);

    return 0;
}