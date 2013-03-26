#include <string>
#include <map>
#include <iostream>

unsigned get_val(const std::string& s) {
    unsigned r=0;
    for(int i=0; i<s.size(); ++i) {
        if (s[i]>='A' && s[i]<='Z')
            r += s[i]-'A'+1;
        else if (s[i]>='a' && s[i]<='z')
            r += s[i]-'a'+1;
    }
    return r;
}

int main() {
    std::map<unsigned, std::string> v;
    int n;
    std::string s;
    std::cin >> n;
    for(int i=0; i<n && std::cin>>s; ++i)
        v[get_val(s)]=s;
    for(auto it=v.begin(); it!=v.end(); ++it)
        std::cout << it->second << '\n';
    return 0;
}