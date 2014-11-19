#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector <int> bigEnough (v1.size ());
    std::copy (v1.cbegin (), v1.cend (), bigEnough.begin ());
    assert (v1 == bigEnough);
    
    std::vector <int> empty;
    std::copy (v1.cbegin (), v1.cend (), std::back_inserter (empty));
    assert (v1 == empty);

    empty.clear ();
    empty.push_back (1);
    empty.push_back (2);
    std::copy (v1.cbegin () + 2, v1.cend (), std::inserter (empty, empty.end ()));
    assert (v1 == empty);
}
