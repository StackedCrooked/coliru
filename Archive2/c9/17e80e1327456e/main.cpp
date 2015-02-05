#include <iostream>
#include <string>

using namespace std;

#define STRINGIFY(x) #x
#define IS_DEFINED(x) AreStringsNotEqual(#x, STRINGIFY(x))

template <size_t N>
static constexpr size_t GetStringLengthImpl(const char (&str)[N], size_t i) {
    return i > N ? N : ( str[i] == '\0'  ? i : GetStringLengthImpl(str, i + 1) );
}

template <size_t N>
static constexpr size_t GetStringLength(const char (&str)[N]) {
    return GetStringLengthImpl(str, 0);
}

template <size_t N1, size_t N2>
static constexpr size_t AreStringsEqualImpl(const char (&str1)[N1], const char (&str2)[N2], size_t i, size_t len) {
    return (i == len) ? true : ( str1[i] != str2[i] ? false : AreStringsEqualImpl(str1, str2, i + 1, len));
}

template <size_t N1, size_t N2>
static constexpr size_t AreStringsEqual(const char (&str1)[N1], const char (&str2)[N2]) {
    return GetStringLength(str1) != GetStringLength(str2) ? false : AreStringsEqualImpl(str1, str2, 0, GetStringLength(str1));
}


template <size_t N1, size_t N2>
static constexpr size_t AreStringsNotEqual(const char (&str1)[N1], const char (&str2)[N2]) {
    return !AreStringsEqual(str1, str2);
}

//////////
//////////

#define COUT_DEFINED(x) #x << STRINGIFY(x)
#define FOO 1
// #define BAR



int main() {
    cout << ( IS_DEFINED(FOO) ? "true" : "false") << endl;
    cout << ( IS_DEFINED(BAR) ? "true" : "false") << endl;
 
 /*
 cout << COUT_DEFINED(FOO) << endl;
 
 cout << GetStringLength("foo") << endl;
 cout << AreStringsEqual("foo", "foo") << endl;
 cout << AreStringsEqual("fo", "foo2") << endl;
 */
 
 return 0;
 
}