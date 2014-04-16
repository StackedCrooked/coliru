#include <numeric>
#include <utility>
#include <string>
using namespace std;

void test(const pair<const int, string> &){} // #1
void test(const pair<int, string> &){} // #2
//template<typename T> void test(T&&){} // #3

int main()
{
    test(make_pair(1, "1"));
}