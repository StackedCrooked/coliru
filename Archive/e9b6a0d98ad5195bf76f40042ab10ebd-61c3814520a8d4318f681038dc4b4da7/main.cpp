#include <iostream>
#include <type_traits>
#include <string>
using namespace std;

template<typename T>
struct A
{
private:
    template<typename AT>
    struct ElementRef
    {
        friend class A;
    protected:
        ElementRef(AT *pa, int row, int col) : m_pa(pa), m_row(row), m_col(col) {}
        AT *m_pa;
        int m_row;
        int m_col;
    public:
        operator const T&() const
        {
            if (is_const<AT>::value) cout << "const ";
            cout << "A(" << m_row << ", " << m_col << ") => const T & (" << m_pa->m_t[m_row][m_col] << ")" << endl;
            return m_pa->m_t[m_row][m_col];
        }

#if 0
        template<typename U>
        typename enable_if<!is_const<AT>::value && is_assignable<T, U&&>::value && !is_same<U, ElementRef>::value, ElementRef>::type operator=(U &&u)
        {
            m_pa->m_t[m_row][m_col] = forward<U>(u);
            cout << "A(" << m_row << ", " << m_col << ") = " << m_pa->m_t[m_row][m_col] << endl;
            return *this;
        }
#endif

        template<typename U>
        typename enable_if<!is_const<AT>::value && is_assignable<T, U&&>::value, const ElementRef>::type operator=(U &&u) const
        {
            m_pa->m_t[m_row][m_col] = forward<U>(u);
            cout << "A(" << m_row << ", " << m_col << ") = " << m_pa->m_t[m_row][m_col] << endl;
            return *this;
        }

#if 1
        ElementRef &operator=(const ElementRef &other)
        {
            cout << "ElementRef::operator=(const ElementRef &other)" << endl;
            m_pa = other.m_pa;
            m_row = other.m_row;
            m_col = other.m_col;
            return *this;
        }
#endif
    };
    
public:
    A() {}
    const ElementRef<A> operator()(int row, int col) { return ElementRef<A>(this, row, col); }
    const ElementRef<const A> operator()(int row, int col) const { return ElementRef<const A>(this, row, col); }
    T m_t[4][4];
};

template<>
A<string>::A()
{
    for (auto &row : m_t)
        for (auto &col : row)
            col = "default";
}

int main()
{
    A<string> a;
    const string &s00 = a(0, 0);
    a(1, 1) = "one";
    const string &s11 = a(1, 1);
    auto e22 = a(2, 2);
    e22 = "two";
    const string &s22 = a(2, 2);
    auto e33 = a(3, 3);
    (e33 = e22) = "three";
    const string &s33 = e33;

    const auto &ca = a;
    const string &sca00 = ca(0, 0);
#ifdef ERROR
    ca(1, 1) = "one";
#endif
    const string &sca11 = ca(1, 1);
#ifdef ERROR
    (ca(2, 2) = ca(0, 0)) = "two";
#endif
    const string &sca22 = ca(2, 2);
    auto ca33 = ca(3, 3);
#ifdef ERROR
    ca33 = "three";
#endif
    const string &sca33 = ca33;
}
