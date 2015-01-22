
#include <iostream>

using namespace std;

template<typename T>
class Node {
    private:
        T v;
    public: 
        Node(T v_) : v(v_) {};
        T getV() const;
};

template<typename T>
T Node<T>::getV() const {
    //i++;    // not possible in a read-only object
    return v;   
}


int main() {
    Node<int> n {345};
    cout << n.getV() <<endl;
    return 0;
}