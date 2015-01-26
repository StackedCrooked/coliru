#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int
main(int argc, char *argv[])
{
    vector<int> vi;
    ostream_iterator<int> it(cout, " ");


    vi.push_back(0);
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(9);
    vi.push_back(8);

    copy(vi.begin(), vi.end(), it);
    cout << endl;

    return 0;
}