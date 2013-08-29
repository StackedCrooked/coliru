#include <iostream>
using namespace std;

class Vec {
public:
    void push_back(int);
    
    Vec() { loc = 0; };
private:
    int loc;
    int array[5];
};

inline void Vec::push_back(int i)
{
    if(loc > 5)
	{
		cerr<<"Vec is already full, remove an element and try again"<<endl
			<<" or cease attempt to add."<<endl;
	}
	else
	{
		array[loc] = i;
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
    v.push_back(7); // but instead prints it here?
    
    return 0;
}