#include <iostream>
#include <vector>
using namespace std;

struct info {
     string name;
     string address;
     int phone;
};


int main(){
    int input;
    cout<<"How many people do you want on the list" <<endl;
    cin>>input;
    std::vector<info>arr(input, info{"", "", 0});
    for(int i = 0; i < input; i++){
        cout<<"Enter name for person " <<i+1 <<": ";
        getline(cin, arr[i].name);
        cin.ignore(1000,'\n');
        cout<<"Enter the address of " <<arr[i].name <<endl;
        getline(cin, arr[i].address);
        cin.ignore(1000, '\n');
        cout<<"Enter phone number of " <<arr[i].name <<endl;
        arr[i].phone;
        cout<<endl;
    }
}