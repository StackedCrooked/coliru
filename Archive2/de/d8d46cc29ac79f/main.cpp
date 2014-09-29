struct GrandParent
{
    GrandParent(int age) : m_age(age) {}
    virtual ~GrandParent() = default;
private:
    GrandParent();
    GrandParent(const GrandParent&);
    const GrandParent& operator=(const GrandParent&);
    int m_age;
};

struct Parent1 : virtual GrandParent
{
    Parent1(int age) : m_age(age) {}
    ~Parent1() = 0;
private:
    Parent1();
    Parent1(const Parent1&);
    const Parent1& operator=(const Parent1&);
    int m_age;
};

inline Parent1::~Parent1() = default;

struct Parent2 : virtual GrandParent
{
    Parent2(int age) : m_age(age) {}
    ~Parent2() = 0;
private:
    Parent2();
    Parent2(const Parent2&);
    const Parent2& operator=(const Parent2&);
    int m_age;
};

inline Parent2::~Parent2() = default;

struct Child : Parent1, Parent2
{
    Child(int grandParentAge, int parent1Age, int parent2Age, int childAge) :
        GrandParent(grandParentAge),
        Parent1(parent1Age),
        Parent2(parent2Age),
        m_age(childAge)
    {}
private:
    Child();
    Child(const Child&);
    const Child& operator=(const Child&);
    int m_age;
};

int main() {
    Child x{60, 36, 34, 10};
}