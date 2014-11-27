#include <iostream>
#include <string>
using namespace std;

class Test {
private:
    int count;
    string name;
public:
    void DoSomethingWithName(){
        cout << "\nCount : " << count << "\nName : " << name << endl;
    }
    Test(int count, string name){
        this->count = count;
        this->name= name;
        DoSomethingWithName();
    }
    Test(int count) {
        Test(count, "");
    }
    Test() {
        Test(0);
    }
};
int main(){
    Test test1;
    Test test2(2);
    Test test3(3, "test");
}