#include <iostream>
using namespace std;

class Outer {
    struct Inner {
        int num;    
    };

public:
 static Inner GetInner() {
    return Inner{-101};
}
};

// void func1(Outer::Inner inner) {  // [1] Does not compile as expected
//  cout << inner.num <<endl;
//}

template <typename Dummy>
void func2(Outer::Inner inner, Dummy = Dummy()) {
    cout << inner.num << endl;
}


int main() {
    // func1(Outer::GetInner()); // [2] does not compile as expected 
    func2<int>(Outer::GetInner()); // [3] How does this compile? 
                                   // Outer::Inner should not be accessible
                                   // from outside Outer
    return 0;
}