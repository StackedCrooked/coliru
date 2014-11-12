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
#include <unordered_map>
#include <vector>
#include <chrono>
#include <iostream>

namespace bmi = boost::multi_index;

std::string getRandomString(size_t length) {
  return "http://www.contoso.com/some/path/someasp.aspx?test=8";
}
std::wstring getRandomWString(size_t length) {
  return L"http://www.contoso.com/some/path/someasp.aspx?test=8";
}

struct VersionData {
  VersionData()
      : m_versionSuffix(L""),
        m_jumpUrl(""),
        m_versionId(-1),
        m_weight(-1),
        m_productId(-1),
        m_hasDefaultImage(false),
        m_isPrefered(false) {}
  VersionData(VersionData&& rhs)
      : m_versionSuffix(std::move(rhs.m_versionSuffix)),
        m_jumpUrl(std::move(rhs.m_jumpUrl)),
        m_versionId(rhs.m_versionId),
        m_weight(rhs.m_weight),
        m_productId(rhs.m_productId),
        m_hasDefaultImage(rhs.m_hasDefaultImage),
        m_isPrefered(rhs.m_isPrefered) {}
  VersionData& operator=(VersionData&& rhs) {
    m_versionSuffix = std::move(rhs.m_versionSuffix);
    m_jumpUrl = std::move(rhs.m_jumpUrl);
    m_versionId = rhs.m_versionId;
    m_weight = rhs.m_weight;
    m_productId = rhs.m_productId;
    m_hasDefaultImage = rhs.m_hasDefaultImage;
    m_isPrefered = rhs.m_isPrefered;
    return *this;
  }
  bool operator==(const VersionData& rhs) const {
    return (m_versionId == rhs.m_versionId);
  }

  bool operator<(const VersionData& rhs) const {
    return (m_versionId < rhs.m_versionId);
  }

  bool operator>(const VersionData& rhs) const {
    return (m_versionId > rhs.m_versionId);
  }

  bool operator==(int version) const { return (m_versionId == version); }

  bool operator<(int version) const { return (m_versionId < version); }

  bool operator>(int version) const { return (m_versionId > version); }

  std::wstring m_versionSuffix;
  std::string m_jumpUrl;
  int m_versionId;
  int m_weight;
  int m_productId;
  bool m_hasDefaultImage;
  bool m_isPrefered;
};

struct VersionsData {
  VersionsData()
      : m_subdeliveryGroupId(-1), m_retargetingId(-1), m_flightName() {}

  VersionsData(int subdeliveryGroupId, int retargetingId,
               std::wstring flightName)
      : m_subdeliveryGroupId(subdeliveryGroupId),
        m_retargetingId(retargetingId),
        m_flightName(flightName) {}

  VersionsData(VersionsData&& rhs)
      : m_subdeliveryGroupId(rhs.m_subdeliveryGroupId),
        m_retargetingId(rhs.m_retargetingId),
        m_flightName(std::move(rhs.m_flightName)) {}

  VersionsData& operator=(VersionsData&& rhs) {
    m_subdeliveryGroupId = rhs.m_subdeliveryGroupId;
    m_retargetingId = rhs.m_retargetingId;
    m_flightName = std::move(rhs.m_flightName);
    return *this;
  }

  bool operator==(const VersionsData& rhs) const {
    return (m_subdeliveryGroupId == rhs.m_subdeliveryGroupId &&
            m_retargetingId == rhs.m_retargetingId &&
            m_flightName == rhs.m_flightName);
  }

  int m_subdeliveryGroupId;
  int m_retargetingId;
  std::wstring m_flightName;
};

struct VersionKeyHasher {
  std::size_t operator()(const VersionsData& rhs) const {
    return ((((std::hash<int>()(rhs.m_subdeliveryGroupId)) ^
              (std::hash<int>()(rhs.m_retargetingId))) ^
             (std::hash<std::wstring>()(rhs.m_flightName))));
  }

  std::size_t operator()(const VersionData& rhs) const {
    return (std::hash<int>()(rhs.m_versionId));
  }
};

class FlatTailoredDSTest {
public:
  FlatTailoredDSTest() : m_data(), m_versions(){
  }
  void wideTest() {
    std::cout << "Populating data." << std::endl;
    populateWide();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      int count = 0;
      std::cout << "Checking isValidVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (isValidVersion(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " valid versions." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasDefaultImage perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasDefaultImage(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " versions with default images." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasPreferedVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasPreferedVersion()) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " prefered versions." << std::endl;
      std::cout << "10m calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking getVersionData perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 200; ++i) {
        for (auto j = 0; j < 200; ++j) {
          for (auto k = 0; k < 250; ++k) {
            count += getVersionData(234567 + i, 123456 + j, L"WideTest");
          }
        }
      }

      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " sum of all version IDs." << std::endl;
      std::cout << "10m calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
  }

  void deepTest() {
    std::cout << "Populating data." << std::endl;
    populateDeep();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      int count = 0;
      std::cout << "Checking isValidVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (isValidVersion(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " valid versions." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasDefaultImage perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasDefaultImage(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " versions with default images." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasPreferedVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasPreferedVersion()) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " prefered versions." << std::endl;
      std::cout << "10m calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking getVersionData perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
          for (auto k = 0; k < 111111; ++k) {
            count += getVersionData(234567 + i, 123456 + j, L"DeepTest");
          }
        }
      }

      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " sum of all version IDs." << std::endl;
      std::cout << "1M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       1000000 << "ns per call." << std::endl << std::endl;
    }
  }

private:
  void populateWide() {
    m_data.clear();
    m_versions.clear();
    int counter = 0;
    for (auto i = 0; i < 200; ++i) {
      for (auto j = 0; j < 200; ++j) {
        for (auto k = 0; k < 25; ++k, ++counter) {
          VersionsData data;
          data.m_flightName = L"WideTest";
          data.m_retargetingId = 123456 + j;
          data.m_subdeliveryGroupId = 234567 + i;

          VersionData version;
          version.m_hasDefaultImage = ((i + j + k) % 2 == 1);
          version.m_isPrefered = ((i + j + k) % 3 == 1);
          version.m_jumpUrl = getRandomString(100);
          version.m_productId = 345678 + i + j + k;
          version.m_versionId = 456789 + counter;
          version.m_versionSuffix = getRandomWString(3);
          version.m_weight = (i + j + k) % 100;
          m_data[std::move(data)].push_back(version.m_versionId);
          m_versions.emplace_back(std::move(version));
        }
      }
    }
    // rearrange
    std::sort(m_versions.begin(), m_versions.end());
    auto newEnd = std::unique(m_versions.begin(), m_versions.end());
    m_versions.resize(std::distance(m_versions.begin(), newEnd));

    for (auto& data : m_data) {
      for (size_t i = 0; i < data.second.size(); ++i) {
        auto findRef = lower_bound(m_versions.cbegin(), m_versions.cend(),
                                   data.second.at(i));
        if (findRef != m_versions.end() &&
            findRef->m_versionId == data.second[i]) {
          VersionRefStorage::reference ref = data.second.at(i);
          data.second[i] = std::distance(m_versions.cbegin(), findRef);
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
    std::cout << "Data size: " << m_versions.size() << std::endl;
  }

  void populateDeep() {
    m_data.clear();
    m_versions.clear();
    int counter = 0;
    for (auto i = 0; i < 3; ++i) {
      for (auto j = 0; j < 3; ++j) {
        for (auto k = 0; k < 111111; ++k, ++counter) {
          VersionsData data;
          data.m_flightName = L"DeepTest";
          data.m_retargetingId = 123456 + j;
          data.m_subdeliveryGroupId = 234567 + i;

          VersionData version;
          version.m_hasDefaultImage = ((i + j + k) % 2 == 1);
          version.m_isPrefered = ((i + j + k) % 3 == 1);
          version.m_jumpUrl = getRandomString(100);
          version.m_productId = 345678 + i + j + k;
          version.m_versionId = 456789 + counter;
          version.m_versionSuffix = getRandomWString(3);
          version.m_weight = (i + j + k) % 100;
          m_data[std::move(data)].push_back(version.m_versionId);
          m_versions.emplace_back(std::move(version));
        }
      }
    }
    // rearrange
    std::sort(m_versions.begin(), m_versions.end());
    auto newEnd = std::unique(m_versions.begin(), m_versions.end());
    m_versions.resize(std::distance(m_versions.begin(), newEnd));

    for (auto& data : m_data) {
      for (size_t i = 0; i < data.second.size(); ++i) {
        auto findRef = lower_bound(m_versions.cbegin(), m_versions.cend(),
                                   data.second.at(i));
        if (findRef != m_versions.end() &&
            findRef->m_versionId == data.second[i]) {
          VersionRefStorage::reference ref = data.second.at(i);
          data.second[i] = std::distance(m_versions.cbegin(), findRef);
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
    std::cout << "Data size: " << m_versions.size() << std::endl;
  }

  bool isValidVersion(int versionId) const {
    auto findRef = lower_bound(m_versions.begin(), m_versions.end(), versionId);
    return (findRef != m_versions.end() && findRef->m_versionId == versionId);
  }

  bool hasDefaultImage(int versionId) const {
    auto findRef = lower_bound(m_versions.begin(), m_versions.end(), versionId);
    if (findRef != m_versions.end() && findRef->m_versionId == versionId &&
        findRef->m_hasDefaultImage) {
      return true;
    } else {
      return false;
    }
  }

  bool hasPreferedVersion() const {
    auto iter =
        find_if(m_versions.begin(), m_versions.end(),
                [&](const VersionData& data) { return data.m_isPrefered; });
    return iter != m_versions.end();
  }

  int getVersionData(int subdeliveryGroupId, int retargetingId,
                     std::wstring flightName) const {
    int retVal = 0;
    VersionsData data;
    data.m_flightName = flightName;
    data.m_retargetingId = retargetingId;
    data.m_subdeliveryGroupId = subdeliveryGroupId;

    auto findIt = m_data.find(data);
    if (findIt != m_data.end()) {
      retVal = 1;
    }
    return retVal;
  }

private:
  typedef std::vector<VersionData> VersionDataContainer;
  typedef std::vector<VersionDataContainer::difference_type> VersionRefStorage;
  typedef std::unordered_map<VersionsData, VersionRefStorage, VersionKeyHasher>
      MassVersionsDataContainer;

  MassVersionsDataContainer m_data;
  VersionDataContainer m_versions;
};

class IntrusiveMICTest {};

namespace boost {
template <> struct hash<VersionsData> {
  size_t operator()(const VersionsData& ecv) const {
    size_t seed = hash_value(ecv.m_flightName);
    hash_combine(seed, ecv.m_retargetingId);
    hash_combine(seed, ecv.m_subdeliveryGroupId);
    return seed;
  };
};
}
class FlyweightMICTest {
public:
  FlyweightMICTest() : m_data(){
  }
  void wideTest() {
    std::cout << "Populating data." << std::endl;
    populateWide();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      int count = 0;
      std::cout << "Checking isValidVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (isValidVersion(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " valid versions." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasDefaultImage perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasDefaultImage(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " versions with default images." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasPreferedVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasPreferedVersion()) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " prefered versions." << std::endl;
      std::cout << "10m calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking getVersionData perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 200; ++i) {
        for (auto j = 0; j < 200; ++j) {
          for (auto k = 0; k < 25; ++k) {
            count += getVersionData(234567 + i, 123456 + j, L"WideTest");
          }
        }
      }

      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " sum of all version IDs." << std::endl;
      std::cout << "1M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       1000000 << "ns per call." << std::endl << std::endl;
    }
  }

  void deepTest() {
    std::cout << "Populating data." << std::endl;
    populateDeep();
    std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
    {
      int count = 0;
      std::cout << "Checking isValidVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (isValidVersion(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " valid versions." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasDefaultImage perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasDefaultImage(456789 + i)) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " versions with default images." << std::endl;
      std::cout << "10M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking hasPreferedVersion perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 10000000; ++i) {
        if (hasPreferedVersion()) {
          count++;
        }
      }
      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " prefered versions." << std::endl;
      std::cout << "10m calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(
                       duration).count() /
                       10000000 << "ns per call." << std::endl << std::endl;
    }
    {
      int count = 0;
      std::cout << "Checking getVersionData perf." << std::endl;
      auto start = std::chrono::high_resolution_clock::now();
      for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
          for (auto k = 0; k < 111111; ++k) {
            count += getVersionData(234567 + i, 123456 + j, L"DeepTest");
          }
        }
      }

      auto duration = std::chrono::high_resolution_clock::now() - start;
      std::cout << count << " sum of all version IDs." << std::endl;
      std::cout << "1M calls took "
                << std::chrono::duration_cast<std::chrono::seconds>(duration)
                       .count() << " seconds or "
                << std::chrono::duration_cast<std::chrono::microseconds>(
                       duration).count() /
                       1000000 << "us per call." << std::endl << std::endl;
    }
  }

private:
  void populateWide() {
    m_data.clear();
    int counter = 0;
    for (auto i = 0; i < 200; ++i) {
      for (auto j = 0; j < 200; ++j) {
        for (auto k = 0; k < 25; ++k, ++counter) {
          FlyweightMICTest::VersionData data(234567 + i, 123456 + j,
                                             L"WideTest");
          data.m_hasDefaultImage = ((i + j + k) % 2 == 1);
          data.m_isPrefered = ((i + j + k) % 3 == 1);
          data.m_jumpUrl = getRandomString(100);
          data.m_productId = 345678 + i + j + k;
          data.m_versionId = 456789 + counter;
          data.m_versionSuffix = getRandomWString(3);
          data.m_weight = (i + j + k) % 100;
          m_data.insert(data);
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
  }

  void populateDeep() {
    m_data.clear();
    int counter = 0;
    for (auto i = 0; i < 3; ++i) {
      for (auto j = 0; j < 3; ++j) {
        for (auto k = 0; k < 111111; ++k, ++counter) {
          FlyweightMICTest::VersionData data(234567 + i, 123456 + j,
                                             L"DeepTest");
          data.m_hasDefaultImage = ((i + j + k) % 2 == 1);
          data.m_isPrefered = ((i + j + k) % 3 == 1);
          data.m_jumpUrl = getRandomString(100);
          data.m_productId = 345678 + i + j + k;
          data.m_versionId = 456789 + counter;
          data.m_versionSuffix = getRandomWString(3);
          data.m_weight = (i + j + k) % 100;
          m_data.insert(data);
        }
      }
    }
    std::cout << "Index size: " << m_data.size() << std::endl;
  }

  bool isValidVersion(int versionId) const {
    auto range = m_data.get<VersionId>().equal_range(versionId);
    return (range.first != range.second);
  }

  bool hasDefaultImage(int versionId) const {
    auto range =
        m_data.get<VerDef>().equal_range(boost::make_tuple(versionId, true));
    return (range.first != range.second);
  }

  bool hasPreferedVersion() const {
    auto range = m_data.get<Prefered>().equal_range(true);
    return (range.first != range.second);
  }

  int getVersionData(int subdeliveryGroupId, int retargetingId,
                     std::wstring flightName) const {
    int retVal = 0;
    auto range = m_data.get<mvKey>().equal_range(
        boost::make_tuple(subdeliveryGroupId, retargetingId, flightName));
    if (range.first != range.second)
      retVal = 1;
    return retVal;
  }

  typedef boost::flyweight<VersionsData> VersionKey;
  struct VersionData {
    VersionData(int subdeliveryGroupId, int retargetingId,
                std::wstring flightName)
        : m_key(subdeliveryGroupId, retargetingId, flightName),
          m_versionSuffix(L""),
          m_jumpUrl(""),
          m_versionId(-1),
          m_weight(-1),
          m_productId(-1),
          m_hasDefaultImage(false),
          m_isPrefered(false) {}
    int getSDGId() const { return m_key.get().m_subdeliveryGroupId; }

    int getRetargetingId() const { return m_key.get().m_retargetingId; }

    std::wstring getFlightName() const { return m_key.get().m_flightName; }

    VersionKey m_key;
    std::wstring m_versionSuffix;
    std::string m_jumpUrl;
    int m_versionId;
    int m_weight;
    int m_productId;
    bool m_hasDefaultImage;
    bool m_isPrefered;
  };

  typedef boost::multi_index_container<
      FlyweightMICTest::VersionData,
      bmi::indexed_by<
          bmi::ordered_non_unique<
              bmi::tag<struct mvKey>,
              bmi::composite_key<
                  FlyweightMICTest::VersionData,
                  bmi::const_mem_fun<FlyweightMICTest::VersionData, int,
                                     &FlyweightMICTest::VersionData::getSDGId>,
                  bmi::const_mem_fun<
                      FlyweightMICTest::VersionData, int,
                      &FlyweightMICTest::VersionData::getRetargetingId>,
                  bmi::const_mem_fun<
                      FlyweightMICTest::VersionData, std::wstring,
                      &FlyweightMICTest::VersionData::getFlightName> > >,
          bmi::ordered_non_unique<
              bmi::tag<struct VersionId>,
              bmi::member<FlyweightMICTest::VersionData, int,
                          &FlyweightMICTest::VersionData::m_versionId> >,
          bmi::ordered_non_unique<
              bmi::tag<struct Prefered>,
              bmi::member<FlyweightMICTest::VersionData, bool,
                          &FlyweightMICTest::VersionData::m_isPrefered> >,
          bmi::ordered_non_unique<
              bmi::tag<struct VerDef>,
              bmi::composite_key<
                  VersionData,
                  bmi::member<FlyweightMICTest::VersionData, int,
                              &FlyweightMICTest::VersionData::m_versionId>,
                  bmi::member<
                      FlyweightMICTest::VersionData, bool,
                      &FlyweightMICTest::VersionData::m_hasDefaultImage> > > > >
      MassVersionsDataContainer;
  MassVersionsDataContainer m_data;
};

int main(int argc, char* argv[]) {
  {
    FlatTailoredDSTest test1;
    test1.deepTest();
    std::cout << "-------------------------------------------------------------"
              << std::endl;
    /*std::cout << "Press any key to continue to next test" << std::endl;
    std::cin.get();*/
    test1.wideTest();
  }
  std::cout << "==============================================================="
            << std::endl;
  /*std::cout << "Press any key to continue to next test" << std::endl;
  std::cin.get();*/
  {
    FlyweightMICTest test2;
    test2.deepTest();
    std::cout << "-------------------------------------------------------------"
              << std::endl;
    /*std::cout << "Press any key to continue to next test" << std::endl;
    std::cin.get();*/
    test2.wideTest();
  }
  std::cout << "==============================================================="
            << std::endl;
  /*std::cout << "Press any key to continue to terminate" << std::endl;
  std::cin.get();*/
  return 0;
}
