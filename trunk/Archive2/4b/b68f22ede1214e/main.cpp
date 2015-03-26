#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

bool isLeapYear(unsigned int year) {
    return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

void leapYearTest() {
    std::cout << isLeapYear(1900) << std::endl;
    std::cout << isLeapYear(1996) << std::endl;
    std::cout << isLeapYear(2000) << std::endl;
    std::cout << isLeapYear(2010) << std::endl;
    std::cout << isLeapYear(2016) << std::endl;
}

//not in place, with buffer string
std::string reverseStringWithBuffer(std::string str) {
    std::string rev = "";
    for(int i = str.size(); i >= 0; --i) {
        rev = rev + str[i];    
    }
    return rev;
}

//in place, index
void reverseStringIndex(char chArr[]) {
    int t, i, j, len = strlen(chArr);
    for(i = 0, j = len-1; i < j; ++i, --j) {
        t = chArr[i];
        chArr[i] = chArr[j];
        chArr[j] = t;
    }
}

//not in place, ptr
void reverseStringPointer(char* chPtr) {
    char t, *e = chPtr + strlen(chPtr)-1;
    
    for(; e > chPtr; ++chPtr, --e) {
        t = *e;
        *e = *chPtr;
        *chPtr = t;
    }
}

void reverseTest() {
    char chArr[] = "Mico";
    std::string str = "Mico";
    std::cout << reverseStringWithBuffer(str) << std::endl;
    reverseStringIndex(chArr);
    std::cout << chArr << std::endl;
    reverseStringPointer(chArr);
    std::cout << chArr << std::endl;
}

bool isPalindrome(std::string str) {
    int i, j;
    for(i = 0, j = str.size()-1; i<j; ++i, --j) {
        if(str[i] != str[j]) return false;
    }
    return true;
}

void palindromeTest() {
    std::cout << isPalindrome("abc") << std::endl;
    std::cout << isPalindrome("abcba") << std::endl;
    std::cout << isPalindrome("abccba") << std::endl;
}

//by ref
void swapRef(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

//by ptr
void swapPtr(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void swapTest()
{
    int a = 0, b = 1;
    swapRef(a, b);
    std::cout << a << " " << b << std::endl;
    swapPtr(&a, &b);
    std::cout << a << " " << b << std::endl;
}

void removeSubstring(std::string& str, std::string rmv) {
    std::size_t pos = 0;
    while ((pos = str.find(rmv, pos)) != std::string::npos) {
        str.replace(pos, rmv.length(), "");
    }
}

void removeSubstringTest() {
    std::string s = "Mico";
    removeSubstring(s, "ico");
    std::cout << s << std::endl;
}

bool isAnagram(std::string s, std::string a) {
    char aArr[100], sArr[100];
    strcpy(aArr, a.c_str());
    strcpy(sArr, s.c_str());
    std::sort(std::begin(aArr), std::end(aArr));
    std::sort(std::begin(sArr), std::end(sArr));
    
    return (aArr == sArr);
}

void anagramTest() {
    std::cout << isAnagram("mico", "oimc");
    std::cout << isAnagram("mico", "oiac");
}

int main()
{
    //http://javarevisited.blogspot.com/2011/06/top-programming-interview-questions.html
    //http://www.journaldev.com/1321/java-string-interview-questions-and-answers
    leapYearTest();
    reverseTest();
    palindromeTest();
    swapTest();
    removeSubstringTest();
    anagramTest();
}
