// MIC stuff
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>

// flyweight implementation stuff
#include <boost/flyweight.hpp>

#include <boost/range/iterator_range.hpp>

#include <string>
#include <vector>
#include <chrono>
#include <iostream>

namespace bmi = boost::multi_index;

std::string getRandomString(size_t length) {
  return "http://www.contoso.com/some/path/someasp.aspx?test=8";
}
std::wstring getRandomWString(size_t length) {
  return L"http://www.contoso.com/some/path/someasp.aspx?test=7";
}

struct TestDataset {
  TestDataset() : m_intMem1(-1), m_intMem2(-1), m_intMem3(-1) {}

  TestDataset(int intData1, int intData2, int flightId)
      : m_intMem1(intData1), m_intMem2(intData2), m_intMem3(flightId) {}

  bool operator==(const TestDataset &rhs) const {
    return (m_intMem1 == rhs.m_intMem1 && m_intMem2 == rhs.m_intMem2 &&
            m_intMem3 == rhs.m_intMem3);
  }

  int m_intMem1;
  int m_intMem2;
  int m_intMem3;
};

struct TestDatasetWS {
  TestDatasetWS() : m_intMem1(-1), m_intMem2(-1), m_strMem3() {}

  TestDatasetWS(int intData1, int intData2, std::wstring strData3)
      : m_intMem1(intData1), m_intMem2(intData2), m_strMem3(strData3) {}

  TestDatasetWS(TestDatasetWS &&rhs)
      : m_intMem1(rhs.m_intMem1), m_intMem2(rhs.m_intMem2),
        m_strMem3(std::move(rhs.m_strMem3)) {}

  TestDatasetWS &operator=(TestDatasetWS &&rhs) {
    m_intMem1 = rhs.m_intMem1;
    m_intMem2 = rhs.m_intMem2;
    m_strMem3 = std::move(rhs.m_strMem3);
    return *this;
  }

  bool operator==(const TestDatasetWS &rhs) const {
    return (m_intMem1 == rhs.m_intMem1 && m_intMem2 == rhs.m_intMem2 &&
            m_strMem3 == rhs.m_strMem3);
  }

  int m_intMem1;
  int m_intMem2;
  std::wstring m_strMem3;
};

class FlyweightMICTest {
public:
  FlyweightMICTest() : m_data() {}

  void deepTest() {
    std::cout << "Populating data." << std::endl;
    populateDeep();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      int count = 0;
      std::cout << "Checking getTestData perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
          for (auto k = 0; k < 111111; ++k) {
            count += getTestData(234567 + i, 123456 + j, 123456789);
          }
        }
      }

      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " sum of all IDs." << std::endl;
      std::cout << "1M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       1000000 << "ns per call." << std::endl << std::endl;
    }
  }

private:
  void populateDeep() {
    m_data.clear();
    int counter = 0;
    for (auto i = 0; i < 3; ++i) {
      for (auto j = 0; j < 3; ++j) {
        for (auto k = 0; k < 111111; ++k, ++counter) {
          FlyweightMICTest::TestData data(234567 + i, 123456 + j, 123456789);
          data.m_boolMem1 = ((i + j + k) % 2 == 1);
          data.m_boolMem2 = ((i + j + k) % 3 == 1);
          data.m_strMem2 = getRandomString(100);
          data.m_intMem3 = 345678 + i + j + k;
          data.m_intMem1 = 456789 + counter;
          data.m_strMem1 = getRandomWString(3);
          data.m_intMem2 = (i + j + k) % 100;
          m_data.insert(data);
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
  }

  int getTestData(int intData1, int intData2, int flightId) const {
    int retVal = 0;
    auto range = m_data.get<mvKey>().equal_range(
        boost::make_tuple(intData1, intData2, flightId));
    if (range.first != range.second)
      retVal = 1;
    return retVal;
  }

  typedef boost::flyweight<TestDataset> TestDataKey;
  struct TestData {
    TestData(int intData1, int intData2, int flightId)
        : m_key(intData1, intData2, flightId), m_strMem1(L""), m_strMem2(""),
          m_intMem1(-1), m_intMem2(-1), m_intMem3(-1), m_boolMem1(false),
          m_boolMem2(false) {}

    int getIntMem1() const { return m_key.get().m_intMem1; }

    int getIntMem2() const { return m_key.get().m_intMem2; }

    int getIntMem3() const { return m_key.get().m_intMem3; }

    TestDataKey m_key;
    std::wstring m_strMem1;
    std::string m_strMem2;
    int m_intMem1;
    int m_intMem2;
    int m_intMem3;
    bool m_boolMem1;
    bool m_boolMem2;
  };

  typedef boost::multi_index_container<
      FlyweightMICTest::TestData,
      bmi::indexed_by<
          bmi::ordered_non_unique<
              bmi::tag<struct mvKey>,
              bmi::composite_key<
                  FlyweightMICTest::TestData,
                  bmi::const_mem_fun<FlyweightMICTest::TestData, int,
                                     &FlyweightMICTest::TestData::getIntMem1>,
                  bmi::const_mem_fun<FlyweightMICTest::TestData, int,
                                     &FlyweightMICTest::TestData::getIntMem2>,
                  bmi::const_mem_fun<FlyweightMICTest::TestData, int,
                                     &FlyweightMICTest::TestData::getIntMem3>>>,
          bmi::ordered_non_unique<
              bmi::tag<struct IntMem1>,
              bmi::member<FlyweightMICTest::TestData, int,
                          &FlyweightMICTest::TestData::m_intMem1>>,
          bmi::ordered_non_unique<
              bmi::tag<struct Prefered>,
              bmi::member<FlyweightMICTest::TestData, bool,
                          &FlyweightMICTest::TestData::m_boolMem2>>>>
      MassTestDatasetContainer;
  MassTestDatasetContainer m_data;
};

size_t hash_value(const TestDataset &ecv) {
  size_t seed = 0;
  boost::hash_combine(seed, ecv.m_intMem3);
  boost::hash_combine(seed, ecv.m_intMem2);
  boost::hash_combine(seed, ecv.m_intMem1);
  return seed;
}

class FlyweightMICTestWithString {
public:
  FlyweightMICTestWithString() : m_data() {}

  void deepTest() {
    std::cout << "Populating data." << std::endl;
    populateDeep();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      int count = 0;
      std::cout << "Checking getTestData perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
          for (auto k = 0; k < 111111; ++k) {
            count += getTestData(234567 + i, 123456 + j, L"DeepTest");
          }
        }
      }

      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " sum of all IDs." << std::endl;
      std::cout << "999999 calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
    				   << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       999999 << "ns per call." << std::endl << std::endl;
    }
  }

private:
  void populateDeep() {
    m_data.clear();
    int counter = 0;
    for (auto i = 0; i < 3; ++i) {
      for (auto j = 0; j < 3; ++j) {
        for (auto k = 0; k < 111111; ++k, ++counter) {
          FlyweightMICTestWithString::TestData data(234567 + i, 123456 + j,
                                                    L"DeepTest");
          data.m_boolMem1 = ((i + j + k) % 2 == 1);
          data.m_boolMem2 = ((i + j + k) % 3 == 1);
          data.m_strMem2 = getRandomString(100);
          data.m_intMem3 = 345678 + i + j + k;
          data.m_intMem1 = 456789 + counter;
          data.m_strMem1 = getRandomWString(3);
          data.m_intMem2 = (i + j + k) % 100;
          m_data.insert(data);
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
  }

  int getTestData(int intData1, int intData2, std::wstring strData3) const {
    int retVal = 0;
    auto range = m_data.get<mvKey>().equal_range(
        boost::make_tuple(intData1, intData2, strData3));
    if (range.first != range.second)
      retVal = 1;
    return retVal;
  }

  typedef boost::flyweight<TestDatasetWS> TestDataKey;
  struct TestData {
    TestData(int intData1, int intData2, std::wstring strData3)
        : m_key(intData1, intData2, strData3), m_strMem1(L""), m_strMem2(""),
          m_intMem1(-1), m_intMem2(-1), m_intMem3(-1), m_boolMem1(false),
          m_boolMem2(false) {}

    int getIntMem1() const { return m_key.get().m_intMem1; }

    int getIntMem2() const { return m_key.get().m_intMem2; }

    std::wstring getStrMem3() const { return m_key.get().m_strMem3; }

    TestDataKey m_key;
    std::wstring m_strMem1;
    std::string m_strMem2;
    int m_intMem1;
    int m_intMem2;
    int m_intMem3;
    bool m_boolMem1;
    bool m_boolMem2;
  };

  typedef boost::multi_index_container<
      FlyweightMICTestWithString::TestData,
      bmi::indexed_by<
          bmi::hashed_non_unique<
              bmi::tag<struct mvKey>,
              bmi::composite_key<
                  FlyweightMICTestWithString::TestData,
                  bmi::const_mem_fun<
                      FlyweightMICTestWithString::TestData, int,
                      &FlyweightMICTestWithString::TestData::getIntMem1>,
                  bmi::const_mem_fun<
                      FlyweightMICTestWithString::TestData, int,
                      &FlyweightMICTestWithString::TestData::getIntMem2>,
                  bmi::const_mem_fun<
                      FlyweightMICTestWithString::TestData, std::wstring,
                      &FlyweightMICTestWithString::TestData::getStrMem3>>>,
          bmi::ordered_non_unique<
              bmi::tag<struct IntMem1>,
              bmi::member<FlyweightMICTestWithString::TestData, int,
                          &FlyweightMICTestWithString::TestData::m_intMem1>>,
          bmi::ordered_non_unique<
              bmi::tag<struct Prefered>,
              bmi::member<FlyweightMICTestWithString::TestData, bool,
                          &FlyweightMICTestWithString::TestData::m_boolMem2>>>>
      MassTestDatasetContainer;
  MassTestDatasetContainer m_data;
};

size_t hash_value(const TestDatasetWS &ecv) {
  size_t seed = 0;
  boost::hash_combine(seed, ecv.m_strMem3);
  boost::hash_combine(seed, ecv.m_intMem2);
  boost::hash_combine(seed, ecv.m_intMem1);
  return seed;
}

int main(int argc, char *argv[]) {
  {
    FlyweightMICTest test2;
    test2.deepTest();
    std::cout << "-------------------------------------------------------------"
              << std::endl;
  }
  {
    FlyweightMICTestWithString test3;
    test3.deepTest();
  }
  std::cout << "==============================================================="
            << std::endl;
  return 0;
}
