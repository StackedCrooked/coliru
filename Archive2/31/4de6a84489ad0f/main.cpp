#include <cstddef>
#include <iostream>
#include <cstring>
class MyClass {
public:
    MyClass(size_t c): count(c) {
        data = new int[count];
    }



    MyClass( MyClass&& src) : count(src.count) {
        data = src.data;
        src.count = 0;
        src.data = nullptr;
        std::cout << "Move constructor.\n";
    }

    void operator=( MyClass&& src) {
        data = src.data;
        count = src.count;
        src.count = 0;
        src.data = nullptr;
        std::cout << "Move assignment.\n";
    }




    ~MyClass() {
        if (data != nullptr)
            delete[] data;
    }

    int* get_data() const {
        return data;
    }

    size_t get_count() const {
        return count;
    }

private:


    int* data;
    size_t count;
};


int main()
{
    MyClass mc(150);
    for (size_t i = 0; i < mc.get_count(); ++i)
        mc.get_data()[i] = i;
    MyClass mc2 = mc;

    return 0;
}