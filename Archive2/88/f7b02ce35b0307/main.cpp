#include <iostream>
#include <string>
using namespace std;

char caesar(char c,int K) {
    if (c <= 'z' && c >= 'a') {
		(char)('a' + ((c - 'a' + K) % 26));
	}
	else if (c <= 'Z' && c >= 'A') {
		(char)('A' + ((c - 'A' + K) % 26));
	}
	else if (c <= '9' && c >= '0') {
		(char)('0' + ((c - '9' + K) % 10));
	}
	cout<<c;
	return c;
}

int main() {

    string str;
    cin>>str;
    int K;
    cin>>K;
	for(size_t i = 0;i<str.length();i++)
    {
        str[i]=caesar(str[i],K);
    }
    cout<<str;
	return 0;
}
