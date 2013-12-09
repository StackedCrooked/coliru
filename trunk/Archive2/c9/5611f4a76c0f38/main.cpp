#include <iostream>

#define GETTIN_STARTED(val) *val
#define GOING_DEEP(val) **val
#define SUB_ZERO(val) ***val
#define MIGHTY_WARRIOR(val) ****val
#define LUDACRIS(val) *****val
#define GODLIKE(val) ******val
#define DEEPER(val) &val
#define FOR(val) for(int i = 0; i < val; i++)

#define GET_ME_ONE_OF_THOSE(val) new int(val)

#define PRINT(val) std::cout << val << std::endl;

#define AUTOMATISCH auto

#define LVL_1 *
#define LVL_2 LVL_1 LVL_1
//#define LVL_4 LVL_2 LVL_2
//#define LVL_8 LVL_4 LVL_4
//#define LVL_16 LVL_8 LVL_8
//#define LVL_32 LVL_16 LVL_16
//#define LVL_64 LVL_32 LVL_32
//#define LVL_128 LVL_64 LVL_64


int main() {
    AUTOMATISCH increment = [&](int GODLIKE(j)) { (GODLIKE(j))++; };
    AUTOMATISCH large_increment = [&](int LUDACRIS(j)) { FOR(5) increment(DEEPER(j)); };
    AUTOMATISCH very_large_increment = [&](int MIGHTY_WARRIOR(j)) { FOR(5) large_increment(DEEPER(j)); };
    AUTOMATISCH very_very_large_increment = [&](int SUB_ZERO(j)) { FOR(5) very_large_increment(DEEPER(j)); };
    AUTOMATISCH very_very_very_large_increment = [&](int GOING_DEEP(j)) { FOR(5) very_very_large_increment(DEEPER(j)); };
    
    AUTOMATISCH GETTIN_STARTED(i) = GET_ME_ONE_OF_THOSE(5);
    very_very_very_large_increment(DEEPER(i));
    
    PRINT(LVL_1(i))
    PRINT(LVL_2(DEEPER(i)))
}
