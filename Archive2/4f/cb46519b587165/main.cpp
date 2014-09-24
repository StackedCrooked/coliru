#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

int level = 0;
void print_indent()
{
    cout << string(level*4,' ');
}

class Integer
{
    string name;
public:
    Integer()
    {
        static int counter = 0;
        stringstream ss;
        ss << "var" << (++counter);
        name = ss.str();
        print_indent();
        cout << "int " << name << "=0;" << endl;
    }
    Integer &operator++()
    {
        print_indent();
        cout << "++" << name << ";" << endl;
        return *this;
    }
    Integer &operator=(const Integer &rhs)
    {
        print_indent();
        cout << name << "=" << rhs.name << ";" << endl;
        return *this;
    }
};
class Block
{
    bool done;
public:
    Block()
        : done(false)
    {
        print_indent();
        cout << "{" << endl;
        ++level;
    }
    bool next()
    {
        return !done;
    }
    void after()
    {
        --level;
        print_indent();
        cout << "}" << endl;
        done = true;
    }
};

#define BLOCK for(Block b##__LINE__;b##__LINE__.next();b##__LINE__.after())

int main()
{
    BLOCK {
        Integer a,b;
        a=b;
        ++a;
        Integer c;
        BLOCK
            a=b=c;
        ++b;
        BLOCK {
            b=++a;
            c=++a;
        }
    }
}