#include <iostream>

struct ChildAtag;
struct ChildBtag;

struct FatherAtag;

template<typename T, typename U>
struct AreEqual { static const bool value = false; };

template<typename T>
struct AreEqual<T, T> { static const bool value = true; };

template<typename T>
struct TagInfo;

template<>
struct TagInfo<ChildAtag>
{ using father = FatherAtag; };

template<typename T>
struct SonOfFatherA
{ static const bool value = AreEqual<typename TagInfo<T>::father, FatherAtag>::value; };

template<typename T, typename Enable = void>
struct Test;

template<typename T>
struct Test<T, typename std::enable_if<SonOfFatherA<T>::value>::type>
{};

int main()
{
    Test<ChildAtag> t;
    
    (void)t;
}