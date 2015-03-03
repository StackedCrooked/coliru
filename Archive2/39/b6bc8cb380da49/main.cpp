#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

string GetUrl(string url){
    string result="Data"+url;
    this_thread::sleep_for(chrono::milliseconds(100));
    return result;
}

int main(){
    auto fun=thread(GetUrl,"MMMMMMMM");
    fun.join();
    cout<<fun<<endl;
    return 0;
    }
