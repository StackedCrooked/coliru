#include <utility>

template <class T>
class MyClass
{
    int count;
    T* data; // Some of them are dynamicly allocated
    
public:
    explicit MyClass() :count(0), data(0) {}
    explicit MyClass(int c) :count(c), data(new T[c]) {}
    MyClass(const MyClass& rhs) :count(0), data(0) {
        try {
            assign(rhs.data, rhs.data+count);
        } catch(...) {
            clear();
            throw;
        }
    }
    
    ~MyClass() {clear();}
    
    MyClass(MyClass&& rhs) :count(), data() {swap(rhs);}
    
    MyClass& operator=(MyClass rhs) {swap(std::move(rhs)); return *this;}
    
    void assign(T* first, T* last) {
        clear();
        data = new T[last-first];
        for (count = 0; count<(last-first); ++count)
            data[count] = first[count];
    }
    
    void clear() {
        for (int i = 0; i<count; i++)
            data[i].~T(); //you forgot this cleanup
        delete[] data;
        count = 0;
        data = 0;
    }
    
    void swap(MyClass rhs) {
        using namespace std;
        swap(count, rhs.count);
        swap(data, rhs.data);
    }
    
};

int main() {
    MyClass<int> inst;
}
        