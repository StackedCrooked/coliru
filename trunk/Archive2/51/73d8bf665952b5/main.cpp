#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct nil {
    static const string create() {return string("");}
};

struct required {};
struct optional {};

template <const char* nm,typename req=required>
struct serial {
    static const string create() {return string(nm)+" INTEGER PRIMARY KEY NOT NULL";}
};

template <const char* nm,typename req=required>
struct integer {
    static const string create() {return string(nm)+" INTEGER NOT NULL";}
};
template <const char* nm>
struct integer<nm,optional> {
    static const string create() {return string(nm)+" INTEGER";}
};

template <typename... DDL>
struct table {
    static const string create() {
        std::string s = "CREATE TABLE (";
        using expander = int[];
        (void)expander{0,(void(s += "\n\t" + DDL::create() + ","),0)...};
        if (sizeof...(DDL)) s.pop_back();
        s += "\n);";
        return s;
    }
};

namespace fields {
    const char id[]="id";
    const char someint[]="someint";
    const char someint2[]="someint2";
};

int main()
{    
    typedef table<
            serial<(const char*)fields::id>,
            integer<(const char*)fields::someint>,
            integer<(const char*)fields::someint2,optional>
    > test;

    cout << test::create() << endl;
}
