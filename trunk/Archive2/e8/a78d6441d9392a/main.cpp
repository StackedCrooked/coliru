#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int main()
{
    bitset<5> inpSeq("10100");
    
    std::vector<int> xorArray;
    
    for (unsigned int i = 0; i < inpSeq.size(); i++) {
        if (inpSeq[i] == 1)
            xorArray.push_back(i);
    }
    
    for (auto x : xorArray)
        cout << x << ' ';
    cout << '\n';
}