#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

class gt100 {
public: 
    bool operator() (int x) { return x>100; } 	
};

int main(){
	char str[] = "Hello world in C++ and STL";
	int len = strlen(str);
	char * pos = find(&str[0], &str[len],'S');
	cout << *pos << endl << endl;


	vector<int> v1;
	v1.push_back(1);
	v1.push_back(11);
	v1.push_back(21);
	v1.push_back(31);
 
	vector<int> v2(v1.size()+2);
	vector <int>::iterator i;
	copy(v1.begin(), v1.end(), v2.begin());
	for (i=v2.begin(); i!=v2.end(); i++)
		cout << *i << " ";
	cout << endl << endl;
	// guess what happens?
	copy_backward(v1.begin(), v1.end(), v2.end());
	for (i=v2.begin(); i!=v2.end(); i++)
		cout << *i << " ";
	cout << endl << endl;
	
	vector<int> iv;
	for (int i = 0; i<20; i++)
		iv.push_back(i*20);
	vector<int>::iterator p;
	p=find_if(iv.begin(),iv.end(),gt100()); // *pos=??
	cout << *p << endl << endl;
	
	//system("pause");
	return 0;
}
