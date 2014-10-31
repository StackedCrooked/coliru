///// TickerInfoManager.hxx
#pragma once

//#include <TickerInfoManagerConstants.h>
#include <string>
#include <memory>

class TickerInfoManager {

  public:
    TickerInfoManager(const char* name);
    ~TickerInfoManager();

    void put(std::string const& id, int total, int active);
    void print_contents() const;

  private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};

///// TickerInfoManager.cxx

#include "TickerInfoManager.hxx"
#include <iostream>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/thread/lock_guard.hpp>

namespace /*anon*/ {
    namespace bip = boost::interprocess;

    typedef bip::allocator<char, bip::managed_shared_memory::segment_manager> CharAllocator;
    typedef bip::basic_string<char, std::char_traits<char>, CharAllocator> SharedString;
    typedef bip::allocator<std::pair<SharedString const, std::pair<int, int> >, bip::managed_shared_memory::segment_manager> MapValueTypeAllocator;
    typedef bip::map<SharedString, std::pair<int, int>, std::less<SharedString>, MapValueTypeAllocator> KeyTickerCountMap;
    typedef boost::lock_guard<bip::interprocess_mutex> lock_guard;

    struct LockableMap {
        LockableMap(MapValueTypeAllocator alloc) : map(alloc) {}

        KeyTickerCountMap       map;
        bip::interprocess_mutex mutex;
    };
}

struct TickerInfoManager::Impl {
    Impl(const char* name)
        : m_segment(bip::open_or_create, name, 1000000),
          m_alloc(m_segment.get_segment_manager()),
          p_data(m_segment.find_or_construct<LockableMap>("TickerInfoMap")(m_segment.get_segment_manager())) 
    {}

    bip::managed_shared_memory   m_segment; // order is relevant
    CharAllocator                m_alloc;
    bip::offset_ptr<LockableMap> p_data;

    KeyTickerCountMap&       map()   { return p_data->map;   }
    bip::interprocess_mutex& mutex() { return p_data->mutex; }
};

TickerInfoManager::TickerInfoManager(const char* name) : pimpl_(new Impl(name)) { }

TickerInfoManager::~TickerInfoManager() { }

void TickerInfoManager::put(std::string const& id, int total, int active) {
    SharedString shid(id.begin(), id.end(), pimpl_->m_alloc);

    lock_guard lock(pimpl_->mutex());
    pimpl_->map()[shid] = { total, active };
}

void TickerInfoManager::print_contents() const {
    lock_guard lock(pimpl_->mutex());
    for (auto const& e : pimpl_->map())
        std::cout << e.first << " " << e.second.first << " " << e.second.second << std::endl;
}

///// **test_stub.cxx**

#include <iostream>
#include <string>
#include "TickerInfoManager.hxx"
#include <thread>

int main() {
    TickerInfoManager tickerinfo("test");
    
    unsigned fullTime = 0;

    while (1) {
        for (int i = 0; i < 30; i++) {
            tickerinfo.put("Deb" + std::to_string(i), i, ++fullTime);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep(1)
        std::cout << "." << std::flush;
    }
}

