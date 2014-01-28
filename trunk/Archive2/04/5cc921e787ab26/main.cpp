# include <iostream>
# include <string>

int main() {
    using namespace std;
    string str1;
    string str2;
    cout<<"the first string"<<endl;
    getline(cin,str1);
    cout<<"the second string"<<endl;
    getline(cin,str2);
    cout<<str1<<endl<<str2<<endl;
}