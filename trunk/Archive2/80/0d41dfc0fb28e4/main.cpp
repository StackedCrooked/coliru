#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
    using namespace std;
    ostreambuf_iterator<char> out(cout);
    for(istreambuf_iterator<char> f(cin >> noskipws), l; f!=l; ++f)
        switch(*f) {
            case '*': return 0;
            case 'a': case 'e': case 'i': case 'o': case 'u': continue; 
            default: *out++ = *f;
        }
}
