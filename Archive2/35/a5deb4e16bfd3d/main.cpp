#include<iostream>
#include<cstring>

char* expand(const char* ptr, int n)
{
    char* p = new char[n];
    strcpy(p, ptr);
    return p;
}

class String{
static const int short_max = 15;
int sz;
char* ptr;
union{
    int space;
    char ch[short_max + 1];
};
public:    
    String() : sz{0}, ptr{ch} { ch[0] = '\0'; }
    explicit String(const char*);
    String& operator=(const String&);
    char* c_str() const { return ptr; }
private:
    void copy_from(const String&);
};

String::String(const char* p) : sz{(int)strlen(p)}, ptr{sz <= short_max ? ch : new char[sz + 1]}, space{0}
{
    strcpy(ptr, p);
}

String& String::operator=(const String& x)
{
    if( this == &x ) return *this;
    char* p = short_max < sz ? ptr : 0;
    copy_from(x);
    delete[] p;
    return *this;
}

void String::copy_from(const String& x)
{
    if( x.sz <= short_max ) {
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    }
    else {
        ptr = expand(x.ptr, x.sz + 1);
        sz = x.sz;
        space = 0;
    }
}

std::ostream& operator<<(std::ostream& os, const String& s) { return os << s.c_str(); }

int main() {
    String s("Belloc");
    s = "JAB";
    std::cout << s << '\n';
}