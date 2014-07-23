#include<memory>
#include<vector>

int main()
{
    std::vector<int> ceva;
    auto deleter = [&]( int* /*rel*/ ){
        //release rel;
        ceva.clear();
    };
    std::unique_ptr<int, decltype(deleter)> ptr(nullptr, deleter);
    ptr.release();
    return 0;
}