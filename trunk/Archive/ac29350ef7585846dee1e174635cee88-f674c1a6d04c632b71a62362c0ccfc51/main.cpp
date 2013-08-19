#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

string upperInput("11101101111000101010");
string lowerInput("01111101100000010100");
vector<bool> upper, lower;

void init()
{   // convert string rows to vector<bool> rows
    for_each(upperInput.begin(), upperInput.end(), [&](char e) { upper.push_back(e == '1'); });
    for_each(lowerInput.begin(), lowerInput.end(), [&](char e) { lower.push_back(e == '1'); });
    assert(upper.size() == lower.size());
}

void dump()
{   // output current content of vector<bool> rows
    for_each(upper.begin(), upper.end(), [] (bool b) { cout << (b ? '1' : '0'); });
    cout << endl;
    for_each(lower.begin(), lower.end(), [] (bool b) { cout << (b ? '1' : '0'); });
    cout << endl;
    cout << endl;
}

bool testWindow(const vector<bool>& source, const vector<bool>::iterator& begin, const vector<bool>::iterator& end)
{
    bool state = *begin; // required state of window
    // value before and after window must be !state
    if ((begin != source.begin() && *(begin - 1) == state) ||
        (end != source.end() && *end == state))
        return false;
    // test if window state is consecutive
    for (auto it = begin + 1; it != end; it++)
        if (*it != state)
            return false;
    return true;
}

void toggle(const vector<bool>::iterator& begin, const vector<bool>::iterator& end)
{
    for (auto it = begin; it != end; it++)
        *it = !*it;
}

int main()
{
    init();
    dump();

    int moves = 0;
    const int n = upper.size();
    for (int windowSize = 1; windowSize <= n; windowSize++)
    {
        for (auto upperWindowBegin = upper.begin(),
                  lowerWindowBegin = lower.begin();
             upperWindowBegin != upper.end() - (windowSize - 1);
             upperWindowBegin++,
             lowerWindowBegin++)
        {
            auto upperWindowEnd = upperWindowBegin + windowSize;
            auto lowerWindowEnd = lowerWindowBegin + windowSize;

            // in last pass (windowSize == n) we will swap complete rows to reach all zeros
            // in all other passes, we will only swap consecutive windows
            bool swapUpperWindow = windowSize == n ? *upperWindowBegin : testWindow(upper, upperWindowBegin, upperWindowEnd);
            bool swapLowerWindow = windowSize == n ? *lowerWindowBegin : testWindow(lower, lowerWindowBegin, lowerWindowEnd);

            if (windowSize == 1 && swapUpperWindow && swapLowerWindow)
            {   // can benifit from toggling column
                moves++;
                cout << "#" << moves << ": Toggling col " << (upperWindowBegin - upper.begin() + 1) << endl;
                toggle(upperWindowBegin, upperWindowEnd);
                toggle(lowerWindowBegin, lowerWindowEnd);
            }
            else
            {
                if (swapUpperWindow)
                {
                    moves++;
                    cout << "#" << moves << ": Toggling " << upperWindowEnd - upperWindowBegin << " lamp(s) in upper row starting from col " << (upperWindowBegin - upper.begin() + 1) << endl;
                    toggle(upperWindowBegin, upperWindowEnd);
                }
                if (swapLowerWindow)
                {
                    moves++;
                    cout << "#" << moves << ": Toggling " << lowerWindowEnd - lowerWindowBegin << " lamp(s) in lower row starting from col " << (lowerWindowBegin - lower.begin() + 1) << endl;
                    toggle(lowerWindowBegin, lowerWindowEnd);
                }
            }
        }
        dump();
    }
    return 0;
}
