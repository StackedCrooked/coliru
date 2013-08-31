// Lamps by Wouter Huysentruit
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <functional>

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

bool testWindow(const vector<bool>& source, const vector<bool>::iterator& begin, const vector<bool>::iterator& end, const bool allowToggleToTrue)
{
    bool state = allowToggleToTrue ? *begin : true; // required state for entire window
    // value before and after window must be !state
    if ((begin != source.begin() && *(begin - 1) == state) ||
        (end != source.end() && *end == state))
        return false;
    // test if window state is consecutive
    for (auto it = begin; it != end; it++)
        if (*it != state)
            return false;
    return true;
}

typedef function<void(bool& swapUpperWindow, bool& swapLowerWindow, const int windowColumn, const int windowSize)> IterateCallback;
bool iterate(vector<bool>& upper, vector<bool>& lower, const int windowSize, const bool allowToggleToTrue, IterateCallback callback)
{
    bool changed = false;

    auto toggle = [] (const vector<bool>::iterator& begin, const vector<bool>::iterator& end)
    {
        for (auto it = begin; it != end; it++)
            *it = !*it;
    };

    for (auto upperWindowBegin = upper.begin(),
              lowerWindowBegin = lower.begin();
         upperWindowBegin != upper.end() - (windowSize - 1);
         upperWindowBegin++,
         lowerWindowBegin++)
    {
        auto upperWindowEnd = upperWindowBegin + windowSize;
        auto lowerWindowEnd = lowerWindowBegin + windowSize;

        bool swapUpperWindow = testWindow(upper, upperWindowBegin, upperWindowEnd, allowToggleToTrue);
        bool swapLowerWindow = testWindow(lower, lowerWindowBegin, lowerWindowEnd, allowToggleToTrue);

        callback(swapUpperWindow, swapLowerWindow, upperWindowBegin - upper.begin() + 1, windowSize);

        if (swapUpperWindow)
            toggle(upperWindowBegin, upperWindowEnd);
        if (swapLowerWindow)
            toggle(lowerWindowBegin, lowerWindowEnd);

        changed |= swapUpperWindow || swapLowerWindow;
    }
    return changed;
}

int main()
{
    init();
    dump();

    int step = 0;
    const int n = upper.size();

    // 1st pass: column toggling
    bool changed = iterate(upper, lower, 1, true, [&step] (bool& swapUpperWindow, bool& swapLowerWindow, const int windowColumn, const int windowSize) {
        if (swapUpperWindow && swapLowerWindow)
            cout << "#" << ++step << ": Toggling column " << windowColumn << endl;
        else
            swapUpperWindow = swapLowerWindow = false;
    });
    if (changed) dump();

    // 2nd pass: enlarge consecutive areas
    for (int windowSize = 1; windowSize <= n; windowSize++)
    {
        bool changed =  iterate(upper, lower, windowSize, false, [&step, &changed] (bool& swapUpperWindow, bool& swapLowerWindow, const int windowColumn, const int windowSize) {
            if (swapUpperWindow)
            {
                cout << "#" << ++step << ": Toggling " << windowSize << " lamp(s) in upper row starting from column " << windowColumn << endl;
                changed = true;
            }
            if (swapLowerWindow)
            {
                cout << "#" << ++step << ": Toggling " << windowSize << " lamp(s) in lower row starting from column " << windowColumn << endl;
                changed = true;
            }
        });
        if (changed) dump();
    }

    cout << "Completed in " << step << " step(s)" << endl;

    return 0;
}
