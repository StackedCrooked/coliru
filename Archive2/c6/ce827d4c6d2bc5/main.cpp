#include <iostream>
#include <string>
#include <vector>

using namespace std;

string formatAnimationFrame(uint64_t particles, size_t length)
{
    string ret;
    particles <<= 64 - length;
    for (; length; --length, particles <<= 1)
        ret += (particles & (1ULL << 63)) ? 'X' : '.';
    return ret;
}

vector<string> generateAnimationSequence(string init, unsigned char speed)
{
    uint64_t left = 0, right = 0;
    const size_t length = init.length();
    const uint64_t mask = ~0ULL >> (64 - length);

    for(auto iter : init)
    {
        left  <<= 1;
        right <<= 1;
        switch (iter)
        {
            case 'L': left  |= 1; break;
            case 'R': right |= 1;
            default : ;
        }
    }

    vector<string> ret;
    for(; (left|right) & mask; left <<= speed, right >>= speed)
        ret.push_back(formatAnimationFrame(left|right, length));
    ret.push_back(formatAnimationFrame(0, length));
    return ret;
}

int main()
{
    string init;
    cin >> init;
    int speed;
    cin >> speed;
    for(auto line : generateAnimationSequence(init, speed))
        cout << line << endl;
    return 0;
}

