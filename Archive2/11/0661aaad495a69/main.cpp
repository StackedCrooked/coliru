#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::placeholders;

int main()
{
    map <string, string> mp1 { {"a", "b"}, {"c", "d"} };
    multimap <string, string> mp2 { {"a", "b"}, {"c", "d"}, {"a", "e"} };

    // Dla zwykłęj mapy odpowiedź zawsze będzie 1 lub 0.
    cerr << mp1.count ("a") << endl; // 1
    
    // Dla multimap może być więcej niż 1
    cerr << mp2.count ("a") << endl; // 2
    
    // SZUKANIE za pomocą find.
    auto i = mp1.find ("c");
    cerr << (i == mp1.end ()) << endl; // 0
    
    i = mp1.find ("ź");
    cerr << (i == mp1.end ()) << endl; // 1
        
    // lower_bound i upper_bound zwracają zakres iteratorów gotowy to użycia w algorytmach:
    auto j = mp2.lower_bound ("a");
    auto k = mp2.upper_bound ("a");
    transform (j, k, ostream_iterator <string> (cout, ","), bind (&decltype (mp2)::value_type::second, _1)); // b,e,

    cerr << endl;

    // Nie ma takiego, ale należałoby wstawić to "ź" na sam koniec:
    j = mp2.lower_bound ("ź");
    cerr << (j == mp2.end ()) << endl; // 1
    
    // Nie ma takiego, ale należałoby wstawić to "_" na początek:
    j = mp2.lower_bound ("_");
    cerr << (j == mp2.begin ()) << endl; // 1

    // A literka "b" powinna być między "a" i "c":
    j = mp2.lower_bound ("b");
    cerr << j->first << endl; // c
    k = mp2.upper_bound ("b");
    cerr << k->first << endl; // też c
    cerr << (j == k) << endl; // 1

    //auto l = mp2.equal_range ("a");
    
}
