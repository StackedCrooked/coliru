#include <boost/range.hpp>
#include <boost/range/any_range.hpp>
#include <boost/range/join.hpp>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

struct TestData {
  TestData() : m_strMem01("test"), m_intMem02(42), m_boolMem03(true) {}
  std::string m_strMem01;
  int m_intMem02;
  bool m_boolMem03;
};

struct IntComp {
  bool operator()(const TestData &s, int i) { return s.m_intMem02 < i; }
  bool operator()(int i, const TestData &s) { return i < s.m_intMem02; }
  bool operator()(const TestData &i, const TestData &s) {
    return i.m_intMem02 < s.m_intMem02;
  }
};
struct StrComp {
  bool operator()(const TestData &s, const std::string &str) {
    return s.m_strMem01 < str;
  }
  bool operator()(const std::string &str, const TestData &s) {
    return str < s.m_strMem01;
  }
  bool operator()(const TestData &i, const TestData &s) {
    return i.m_strMem01 < s.m_strMem01;
  }
};

typedef boost::any_range<TestData, boost::forward_traversal_tag,
                         const TestData &, std::ptrdiff_t> TestRange;

std::vector<TestData> vecData(10);
std::list<TestData> listData(20);

TestRange foo() {
  TestRange retVal;

  auto tmp1 = std::equal_range(vecData.cbegin(), vecData.cend(), 42, IntComp());
  retVal = boost::join(retVal, tmp1);
  auto tmp2 =
      std::equal_range(listData.cbegin(), listData.cend(), "test", StrComp());
  retVal = boost::join(retVal, tmp2);
  return retVal;
}

int main(int argc, char *argv[]) {
  auto res = foo();
  for (auto a : res) {
    std::cout << a.m_strMem01 << std::endl;
  }
  //std::cout << res[4].m_intMem02 << std::endl;
}
