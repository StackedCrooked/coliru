#include <cstddef>
#include <iostream>
#include <cstring>
class MyClass {
public:
    MyClass(size_t c): count(c) {
        data = new int[count];
    }

    MyClass( const MyClass& other) = default;
    void operator=( const MyClass& other) = default;

    MyClass( MyClass&& src) delete;

    void operator=( MyClass&& src) = delete;




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
    MyClass mc2 = std::move(mc);

    return 0;
}