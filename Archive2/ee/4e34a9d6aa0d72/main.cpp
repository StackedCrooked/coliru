#include <iostream>

template <class T> class pure {
public:
    pure(T const& attr) {
        this->attr = attr;
    }

    ~pure() {
    }

    T& operator=(T const& attr) {
        return attr;
    }

    operator T() {
        return this->attr;
    }
    
    template <typename U>
    operator U() = delete;

private:
    T attr;
};

int main()
{
    pure<int> i(3);
    std::cout << (int)i;
    std::cout << (long)i;
}