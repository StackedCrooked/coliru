template <class T>
class MyClass
{
    explicit MyClass() :count(0), data(0) {}
    explicit MyClass(int c) :count(c), data(new T[c]) {}
    MyClass(const MyClass& rhs) :count(0), data(0) {
        try {
            assign(rhs.data, rhs.data+count);
        } catch(...) {
            destroy();
            throw;
        }
    }
    
    ~MyClass() {destroy();}
    
    MyClass(MyClass&& rhs) :count(), data() {swap(rhs);}
    
    MyClass& operator=(MyClass rhs) {swap(std::move(rhs)); return *this;}
    
    void assign(T* first, T* last) {
        destroy();
        data = new T[last-first];
        for (count = 0; count<(last-first); ++count)
            data[i] = myClass.data[i];
    }
    
    void swap(MyClass rhs) {
        using namespace std;
        swap(count, rhs.count);
        swap(data, rhs.data);
    }
    
private:
    
    void destroy() {
        for (i = 0; i<count; i++)
            data[i].~myClass(); //you forgot this cleanup
        delete[] data;
        count = 0;
        data = 0;
    }
    
    // Data members
    int count;
    T* data; // Some of them are dynamicly allocated
}
        