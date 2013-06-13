#include <iostream>
using namespace std;

class Vec {
public:
    void push_back(int);
private:
    int loc;
    int array[5];
};

inline void Vec::push_back(int i)
{
    if(loc > 5)
	{
		cerr<<"Vec is already full, remove an element and try again"<<endl;
			<<" or cease attempt to add."<<endl;
	}
	else
	{
		cout<<push_back(" << i << ")
			<<loc<<endl;
		array[loc] = 1;
		++loc;
	}
}

int main() {
    Vec v;
    
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6); // should print the error message here
    
    return 0;
}