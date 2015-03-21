#include <iostream>

struct StructB
{
    char data[16];
    char someChar;
    char otherChars[3];
};    

struct StructA
{
    StructB structB;
    uint8_t someArray[8];
    uint8_t someOtherArray[8];
};

//#if defined PLATFORM_A
//    typedef StructA Id;
//#else defined PLATFORM_B
    typedef uint64_t Id;
//#endif


//Scenario B
class UserId
{
public:
    UserId() {};
    UserId(const Id& id) : m_userId(id) {};
    UserId(const UserId& otherUserId) : m_userId(otherUserId.m_userId) {};


    Id m_userId;
};

int main() {
     UserId userId;
//#if defined PLATFORM_A
//    StructA structA;
//    //do some work to populate structA
//    userId = UserId(structA);
//#else
    uint64_t thisUserId = 123; //get the id
    userId = UserId(thisUserId);
//#endif

    //userId is valid here in scenario A, but not scenario B.  Why?   
    std::cout << userId.m_userId << std::endl;
}