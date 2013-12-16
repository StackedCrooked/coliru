#include <iostream>

#define GETTIN_STARTED(val) *val
#define GOING_DEEP(val) **val
#define SUB_ZERO(val) ***val
#define MIGHTY_WARRIOR(val) ****val
#define LUDACRIS(val) *****val
#define GODLIKE(val) ******val
#define DEEPER(val) &val
#define FOR(val) for(int i = 0; i < val; i++)

void increment(int GODLIKE(j)) { (GODLIKE(j))++; }
void large_increment(int LUDACRIS(j)) { FOR(5) increment(DEEPER(j)); }
void very_large_increment(int MIGHTY_WARRIOR(j)) { FOR(5) large_increment(DEEPER(j)); }
void very_very_large_increment(int SUB_ZERO(j)) { FOR(5) very_large_increment(DEEPER(j)); }
void very_very_very_large_increment(int GOING_DEEP(j)) { FOR(5) very_very_large_increment(DEEPER(j)); }

int main() {
    int GETTIN_STARTED(i) = new int(5);
    very_very_very_large_increment(DEEPER(i));
    std::cout << *i << std::endl;
}
