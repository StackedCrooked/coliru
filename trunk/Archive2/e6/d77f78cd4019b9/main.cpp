//#include "mainwindow.h"
#include <map>
using namespace std;

using Value     = int;
using Occurence = unsigned;
using Histo     = map<Value, Occurence>;

void MergeInto(Histo& target, Histo const& other)
{
    auto left_it  = begin(target), left_end  = end(target);
    auto right_it = begin(other),  right_end = end(other);
    auto const& cmp = target.value_comp();

    while (right_it != right_end)
    {
        if ((left_it == left_end) || cmp(*right_it, *left_it))
        {
            // insert at left_it
            target.insert(left_it, *right_it);
            ++right_it; // and carry on
        } else if (cmp(*left_it, *right_it))
        {
            ++left_it; // keep left_it first, so increment it
        } else
        {
            // keys match!
            left_it->second += right_it->second;
            ++left_it;
            ++right_it;
        }
    }
}

// convenience
Histo Merge(Histo const& left, Histo const& right)
{
    auto copy(left);
    MergeInto(copy, right);
    return copy;
}

#include <iostream>

// for debug output
static inline std::ostream& operator<<(std::ostream& os, Histo::value_type const& v) { return os << "{" << v.first << "," << v.second << "}"; }
static inline std::ostream& operator<<(std::ostream& os, Histo const& v) { for (auto& el : v) os << el << " "; return os; }
//


#include <iomanip>

int main(int argc, char *argv[])
{
    Histo A { { 8, 1 }, { 5, 1 } };
    Histo B { { 2, 1 }, { 8, 1 } };
    auto C = Merge(A, B);

    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";
    std::cout << "C: " << C << "\n";
}
