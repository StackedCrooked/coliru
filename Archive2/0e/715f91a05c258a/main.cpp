#include <string>

using namespace std;

class Base
{
public:
    Base(int tagId, const string& value) : m_tagId(tagId), m_value(value) { }
    virtual ~Base() { }

    virtual string value() { return m_value; }

    virtual Base& operator=(const string& value)
    {
        m_value = value;
        return *this;
    }

    virtual Base& operator=(const Base& rhs)
    {
        if (this != &rhs)
        {
            m_tagId = rhs.m_tagId;
            m_value = rhs.m_value;
        }
        return *this;
    }

private:
    int m_tagId;
    string m_value;
};

class Derived : public Base
{
public:
    Derived(int tagId, const string& value) : Base(tagId, value) { }
    virtual ~Derived() { }
};

int main()
{
    Derived a(0, "String A");
    a.operator=("String B");    // aka: a = "String B";
}