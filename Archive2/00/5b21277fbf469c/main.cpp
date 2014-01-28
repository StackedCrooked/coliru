//OK MON VS PU LA MERDE
#include <iostream>
#include <vector>

using namespace std;

template<typename func>
void filter(func f, vector<int> arr) {
    for (auto i: arr) {
		if (f(i))
			cout<<i<<" ";
	}
}

bool myboo(int x)
{
	if(x > 9)
		return true;
	return false;
}

int main(){
	auto v = {14, 16, 8, 3, 11, 10, 5};
	filter(myboo, v);
	return 0;
}