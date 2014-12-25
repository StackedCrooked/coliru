#include <boost/flyweight.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include <string>
#include <chrono>
#include <iostream>
#include <numeric>

namespace bmi = boost::multi_index;

struct DataKey {
  DataKey(int intData01, int intData02, const std::wstring &strData03);
  DataKey(DataKey &&rhs);
  DataKey &operator=(DataKey &&rhs);
  bool operator==(const DataKey &rhs) const;
  std::wstring m_strData03;
  int m_intData01;
  int m_intData02;

private:
  DataKey(const DataKey &);
  DataKey &operator=(const DataKey &);
};

typedef boost::flyweight<DataKey> Key;

struct Data {
  Data(int intData01, int intData02, std::wstring strData03);
  Data(Data &&rhs);
  Data &operator=(Data &&rhs);
  bool operator==(const Data &rhs) const;
  bool operator<(const Data &rhs) const;
  int getIntData01() const { return m_key.get().m_intData01; }
  int getIntData02() const { return m_key.get().m_intData02; }
  const std::wstring &getStrData03() const { return m_key.get().m_strData03; }

  Key m_key;
  std::wstring m_strMem01;
  std::string m_strMem02;
  int m_intMem03;
  int m_intMem04;
  int m_intMem05;
  int m_intMem06;
  int m_intMem07;
  bool m_boolMem08;
  bool m_boolMem09;

private:
  Data(const Data &);
  Data &operator=(const Data &);
};

size_t hash_value(const DataKey &key);

typedef boost::multi_index_container < Data,
    bmi::indexed_by <
        bmi::ordered_non_unique<
            bmi::tag<struct byKey>,
            bmi::composite_key<
                Data, bmi::const_mem_fun<Data, int, &Data::getIntData01>,
                bmi::const_mem_fun<Data, int, &Data::getIntData02>,
                bmi::const_mem_fun<Data, const std::wstring &,
                                   &Data::getStrData03>>>,
                bmi::ordered_non_unique<
                    bmi::tag<struct byMem>,
                    bmi::member<Data, int, &Data::m_intMem03>>>> DataContainer;

typedef boost::iterator_range<DataContainer::index<byKey>::type::const_iterator> DataRange;

using namespace std;

size_t hash_value(const DataKey &key) {
  size_t seed = 0;
  boost::hash_combine(seed, key.m_strData03);
  boost::hash_combine(seed, key.m_intData02);
  boost::hash_combine(seed, key.m_intData01);
  return seed;
}

Data::Data(int intData01, int intData02, std::wstring strData03)
    : m_key(intData01, intData02, strData03), m_strMem01(L""), m_strMem02(""),
      m_intMem03(-1), m_intMem04(0), m_intMem05(0), m_intMem06(0),
      m_intMem07(-1), m_boolMem08(false), m_boolMem09(false) {}

Data::Data(Data &&rhs)
    : m_key(std::move(rhs.m_key)), m_strMem01(std::move(rhs.m_strMem01)),
      m_strMem02(std::move(rhs.m_strMem02)), m_intMem03(rhs.m_intMem03),
      m_intMem04(rhs.m_intMem04), m_intMem05(rhs.m_intMem05),
      m_intMem06(rhs.m_intMem06), m_intMem07(rhs.m_intMem07),
      m_boolMem08(rhs.m_boolMem08), m_boolMem09(rhs.m_boolMem09) {}

Data &Data::operator=(Data &&rhs) {
  m_key = std::move(rhs.m_key);
  m_strMem01 = std::move(rhs.m_strMem01);
  m_strMem02 = std::move(rhs.m_strMem02);
  m_intMem03 = rhs.m_intMem03;
  m_intMem04 = rhs.m_intMem04;
  m_intMem05 = rhs.m_intMem05;
  m_intMem06 = rhs.m_intMem06;
  m_intMem07 = rhs.m_intMem07;
  m_boolMem08 = rhs.m_boolMem08;
  m_boolMem09 = rhs.m_boolMem09;
  return *this;
}

bool Data::operator==(const Data &rhs) const {
  return (rhs.m_intMem03 == m_intMem03);
}

bool Data::operator<(const Data &rhs) const {
  return (rhs.m_intMem03 < m_intMem03);
}

DataKey::DataKey(int intData01, int intData02, const std::wstring &strData03)
    : m_strData03(strData03), m_intData01(intData01), m_intData02(intData02) {}

DataKey::DataKey(DataKey &&rhs)
    : m_strData03(std::move(rhs.m_strData03)), m_intData01(rhs.m_intData01),
      m_intData02(rhs.m_intData02) {}

DataKey &DataKey::operator=(DataKey &&rhs) {
  m_intData01 = rhs.m_intData01;
  m_intData02 = rhs.m_intData02;
  m_strData03 = std::move(rhs.m_strData03);
  return *this;
}

bool DataKey::operator==(const DataKey &rhs) const {
  return (m_intData01 == rhs.m_intData01 && m_intData02 == rhs.m_intData02 &&
          m_strData03 == rhs.m_strData03);
}

class MICTest {
public:
  MICTest() : m_data() {}

  void deepTest() {
    std::cout << "Populating data." << std::endl;
    populateDeep();
    //std::cin.get();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      std::cout << "Checking getVersionData perf." << std::endl;
      auto start1 = std::chrono::high_resolution_clock::now();
      auto data = getData(234567, 123456, L"DeepTest");
      auto duration1 = std::chrono::high_resolution_clock::now() - start1;
      std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                       duration1).count() << "ms for data retrieval." << std::endl
                << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      auto res = std::accumulate(
          data.begin(), data.end(), 0,
          [&](int init, const Data &rhs) { return init + rhs.m_intMem07; });
          auto size = boost::size(data);
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << size << " entities retrieved." << std::endl;
      std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                       duration).count() << "ms for all calulations." << std::endl
                << std::endl;
    }
  }

private:
  void populateDeep() {
    m_data.clear();
    int counter = 0;
    for (auto i = 0; i < 10; ++i) {
      for (auto j = 0; j < 10; ++j) {
        for (auto k = 0; k < 11111; ++k, ++counter) {
          Data data(234567, 123456, L"DeepTest");
          data.m_boolMem08 = ((i + j + k) % 2 == 1);
          data.m_boolMem09 = ((i + j + k) % 3 == 1);
          data.m_strMem02 = "Test";
          data.m_intMem07 = 345678 + i + j + k;
          data.m_intMem03 = 456789 + counter;
          data.m_strMem01 = L"TestTestTest";
          data.m_intMem04 = (i + j + k) % 100;
		  auto res = m_data.emplace(std::move(data));
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
  }

  DataRange getData(int intData01, int intData02,
                    const std::wstring &strData03) const {
    return m_data.get<byKey>().equal_range(
        boost::make_tuple(intData01, intData02, strData03));
  }

  DataContainer m_data;
};

int main(int argc, char *argv[]) {

  {
    MICTest test3;
    test3.deepTest();
	//std::cin.get();
  }
  std::cout << "==============================================================="
            << std::endl;
  return 0;
}
