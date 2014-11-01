#include <iostream>
#include <string>
using namespace std;

struct Counter{
    static int k;
	Counter(){ k++; }
	~Counter() { k--; }
};
int Counter::k = 0;
#define LOL(x) {string s = #x; Counter c##x; cout<<s.substr(0,1+s.find('['))<<Counter::k<<"]="<<x<<'\n'; }

int main()
{
    int test[4] = {10, 5, 4};
    LOL(test[0]);
}
