#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
int strlen(const char* s){
    int i = 0;
    while(*s++ != '\0'){
        i++;
    }
    return i;
}

int strlen(const std::string& s){
    int i = 0;
    for(std::string::const_iterator j = s.begin(); j!=s.end(); j++)
        i++;
    return i;
}


int main()
{
    std::string c = "test";
    //cout << strlen(c);
    //cout << strlen("test");
    static const char* const letters[] = {"A+","A","B+","ABCDEF"};
    cout << letters[3];
    static const double numbers[] = {1,2,3,4,5};
    cout << sizeof(numbers);
}
