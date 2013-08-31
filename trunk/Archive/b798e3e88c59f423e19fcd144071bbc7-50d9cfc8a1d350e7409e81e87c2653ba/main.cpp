#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  const char s[6] ="Hello";                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  X x1;
  X x2(1);
}

