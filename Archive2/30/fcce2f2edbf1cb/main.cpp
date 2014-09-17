#include <iostream>
#include <cstdlib>
#include <string.h>

class string;

class RValueRefString {
    friend class string;
    private:
    char* data; size_t sz;
    public:
    RValueRefString(const char* p) { sz = strlen(p) + 1; data = new char[sz]; memcpy(data, p, sz); }
    RValueRefString(RValueRefString& r) { if ( this != &r ) { delete[] data; sz = r.sz; data = r.data; r.sz = 0; r.data = NULL; } }
    ~RValueRefString() { delete[] data; }
    RValueRefString(const string& rStr1, const string& rStr2);
};

class string {
    friend class RValueRefString;
    char* data; 
    public:
    string(const char* p) { size_t size = strlen(p) + 1; data = new char[size]; memcpy(data, p, size); }
    ~string() { delete[] data; }
    string(const string& that) { size_t size = strlen(that.data) + 1; data = new char[size]; memcpy(data, that.data, size); }
    string(RValueRefString& r) { data = r.data; r.sz = 0; r.data = NULL; } void operator = (RValueRefString& that) { delete[] data; size_t size = that.sz; data = new char[size]; memcpy(data, that.data, size); } const char* get() const { return data; }
};

RValueRefString::RValueRefString(const string& rStr1, const string& rStr2) {
    size_t sz1 = strlen(rStr1.data); size_t sz2 = strlen(rStr2.data); sz = sz1 + sz2 + 1; data = new char[sz]; memcpy(data, rStr1.data, sz1); memcpy(data + sz1, rStr2.data, sz2 + 1);
}

RValueRefString operator + (const string& rStr1, const string& rStr2) { return RValueRefString(rStr1, rStr2); }
int main() {
    string strA("abc"); string strB("def"); string strC = strA + strB; std::cout << strC.get() << std::endl; std::cout << "the end" << std::endl;
}
