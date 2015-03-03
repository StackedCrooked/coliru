#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <future>
using namespace std;

string GetUrl(string url){
    string result="Data"+url;
    this_thread::sleep_for(chrono::milliseconds(100));
    return result;
}

int main(){
    auto fun::std async(GetUrl,"MMMMMMMM");
    string example=future.get();
    cout<<example<<endl;
    return 0;
    }
