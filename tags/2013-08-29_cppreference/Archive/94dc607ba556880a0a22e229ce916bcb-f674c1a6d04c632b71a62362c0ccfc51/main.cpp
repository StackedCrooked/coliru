// Solution for http://stackoverflow.com/questions/18303383/i-require-some-assistance-with-this-c-algorithm
// by Wouter Huysentruit
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <functional>

using namespace std;

const string upperInput("11101101111000101010");
const string lowerInput("01111101100000010100");
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

// iterate over both rows with callback
typedef function<void (const vector<bool>::iterator& itUpper, const vector<bool>::iterator& itLower)> IteratorCallback;
void iterate(const bool includeEnd, const IteratorCallback callback)
{
    for (auto itUpper = upper.begin(), itLower = lower.begin(); itUpper != upper.end(); itUpper++, itLower++)
        callback(itUpper, itLower);
    if (includeEnd)
        callback(upper.end(), lower.end());
}

int main()
{
    init();

    cout << "Initial rows data: " << endl;
    dump();

    int steps = 0;

    // a state is isolated if the state before and after holds the opposite value or is an isolated 1 at the beginning or end.
    const auto isIsolatedState = [] (const vector<bool>& source, const vector<bool>::iterator& it) {
        return (it != source.begin() && it != source.end() && *(it - 1) != *it && *(it + 1) != *it)
            || (it == source.begin() && *it && !*(it + 1))
            || (it == source.end()   && *it && !*(it - 1));
    };

    // toggle consecutive states in the given range
    const auto toggle = [] (const vector<bool>::iterator& begin, const vector<bool>::iterator& end)
    {
        for (auto it = begin; it != end; it++)
            *it = !*it;
    };

    auto upperBlockStart = upper.front() ? upper.begin() : upper.end();
    auto lowerBlockStart = lower.front() ? lower.begin() : lower.end();
    iterate(true, [&upperBlockStart, &lowerBlockStart, &steps, isIsolatedState, toggle] (const vector<bool>::iterator& itUpper, const vector<bool>::iterator& itLower) {
        // toggle columns if state in both rows is isolated
        if (itUpper != upper.end())
        {
            const int column =  itUpper - upper.begin() + 1;
            if (isIsolatedState(upper, itUpper) && isIsolatedState(lower, itLower))
            {
                cout << "#" << ++steps << ": Toggling column " << column << endl;
                toggle(itUpper, itUpper + 1);
                toggle(itLower, itLower + 1);
                dump();
            }
        }

        // keep track of blocks with 1's in upper row
        const bool upperState = itUpper != upper.end() ? *itUpper : false;
        if (upperState && upperBlockStart == upper.end())
            upperBlockStart = itUpper; // start of block of 1's in upper row
        if (!upperState && upperBlockStart != upper.end())
        {   // end of block of 1's in upper row
            const int count = itUpper - upperBlockStart;
            const int column = upperBlockStart - upper.begin() + 1;
            cout << "#" << ++steps << ": Toggling " << count << " lamp(s) in upper row starting from column " << column << endl;
            toggle(upperBlockStart, itUpper);
            upperBlockStart = upper.end();
            dump();
        }

        // keep track of blocks with 1's in lower row
        const bool lowerState = itLower != lower.end() ? *itLower : false;
        if (lowerState && *itLower && lowerBlockStart == lower.end())
            lowerBlockStart = itLower; // start of block of 1's in lower row
        if (!lowerState && lowerBlockStart != lower.end())
        {   // end of block of 1's in lower row
            const int count = itLower - lowerBlockStart;
            const int column = lowerBlockStart - lower.begin() + 1;
            cout << "#" << ++steps << ": Toggling " << count << " lamp(s) in lower row starting from column " << column << endl;
            toggle(lowerBlockStart, itLower);
            lowerBlockStart = lower.end();
            dump();
        }
    });

    cout << "Solved in " << steps << " step(s)" << endl;

    return 0;
}
