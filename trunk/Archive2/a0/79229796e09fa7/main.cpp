#include <iostream>

using namespace std;

template <class T>
class Queue
{
private:
    T* arr;
    int capacity;
    int next, oldest;
    int size;
    void resize()
    {
        cout << "resize..." << endl;
        show();

        T* new_arr = new T[capacity*2];

        int o = oldest;
        for (int i = 0; i < size; i++, o++)
        {
            new_arr[i] = arr[o];
        }
        next = size;
        oldest = 0;

        delete[] arr;
        arr = new_arr;
        capacity *= 2;
        show();
        cout << "resize done" << endl;
    }

public:
    Queue(int initial = 10)
    {
        arr = new T[capacity = initial];
        next = oldest = size = 0;
    }
    ~Queue()
    {
        delete[] arr;
    }
    void enqueue(const T &elem)
    {
        //cout << "enqueue..." << endl;
        if (size == capacity) { resize(); }
        arr[next++] = elem;
        next %= capacity;
        ++size;
    }
    T dequeue()
    {
        cout << "dequeue: ";
        if (!size) return 0;
        T ret = arr[oldest++];
        oldest %= capacity;
        --size;
        cout << ret << endl;
        return ret;
    }
    T* peek()
    {
        return arr[oldest];
    }

    int getSize() { return size; }

    void show()
    {
        
//        cout << "capacity: " << capacity << " size: " << size << " oldest: " << oldest << " next: " << next << endl << "elements: ";
//
//        int i = 0;
//        int o = oldest;
//        while(i < size)
//        {
//            cout << arr[o] << " ";
//            ++o %= capacity;
//            ++i;
//        }
//        cout << endl;

        cout << "blaaaaa" << endl;
    }

};
class A
{
private:
    int m1;
    int m2;
public:
    A(int a1 = 0, int a2 = 0)
    {
        m1 = a1; m2 = a2;
    }
};

int main()
{
    cout << "Hello World!" << endl;



    A a(3,4);

    Queue<A> q2;
    q2.show();

    cout << "done." << endl;
    return 0;
}

