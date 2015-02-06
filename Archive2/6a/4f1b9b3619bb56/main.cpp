
#include <future>
#include <iostream>
using namespace std;



void test(int x){
    cout << x << endl;
}

int main(){

    auto handle = std::async(test,0);
    test(1);
    handle.get();

}

