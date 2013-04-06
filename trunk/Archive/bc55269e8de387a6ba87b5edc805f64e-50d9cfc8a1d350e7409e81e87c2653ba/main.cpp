#include <iostream>
#include <string>
#include <vector>

struct X
{
  X() : m_a() {}             // well-formed
  X(int (&a)[3]) : m_a{a} {} // ill-formed; however, compiler-generated copy constructors may do this; see ConstructorPrologProcessor::BaseOrMemberProcessor::Process
  X(int) : m_a(1, 2, 3) {}   // ill-formed
  X(char) : m_a{1, 2, 3} {}  // well-formed; new behavior in C++11

  int m_a[3];
  int m_b1[3]{};           // well-formed
  int m_b2[3] = {};        // well-formed
  int m_b3[3]{1, 2, 3};    // well-formed
  int m_b4[3] = {1, 2, 3}; // well-formed
  int m_b5[3]{m_a};          // ill-formed
  int m_b6[3] = m_a;       // ill-formed
};

int main()
{
}
