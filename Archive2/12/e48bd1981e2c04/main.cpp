#include <iostream>
#include <iterator>
#include <list>
using namespace std;

template <typename C>
void print(const C &data){
    for(auto it=begin(data);it!=end(data);++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}


int main(int argc, char** argv) {
    list<int> data;
    for(int i=0;i<4;i++){
        data.push_back(i);
    }
    print(data);
    return 0;
}