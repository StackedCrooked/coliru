#include <cstdio>
#include <map>
using namespace std;

int main() {
    map<char, int> m;
    printf("Size before adding: %d\n", m.size());
    
    auto size = m.size();
    m['A'] = size;
    
    printf("Size after adding: %d\n", m.size());
    printf("What was added: %d\n", m['A']);

    return 0;
}