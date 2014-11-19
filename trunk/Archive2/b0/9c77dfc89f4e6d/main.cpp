#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
//#include <boost/fusion/sequence.hpp>
//#include <boost/fusion/include/sequence.hpp>
//#include <boost/fusion/adapted/struct/adapt_struct.hpp>
//#include <boost/fusion/include/adapt_struct.hpp>

namespace client {
    struct key;
    bool operator < (const key& l, const key& r);
    
    struct key {
        key() {}
        key(const key& other) : attrs(other.attrs) {}
        key(const std::initializer_list<std::string>& l) : attrs(l) {}
        std::vector<std::string> attrs;
        bool operator()(const key& l, const key& r) {
            return l.attrs[0] < r.attrs[0] && l.attrs[1] < r.attrs[1];
        }
    };
}

namespace user_info {
    struct entry {
        entry(const std::initializer_list<std::pair<std::string, std::string>>& l) : attrs(l) {}
        std::vector<std::pair<std::string, std::string>> attrs;
    };
    typedef std::shared_ptr<entry> entry_ptr_t;
    typedef std::vector<entry_ptr_t> entry_ptr_vec_t;
    
    template<typename IndexTraits>
    class storage {
    public:
        typedef std::map<IndexTraits, entry_ptr_t, IndexTraits> index_t;
    public:
        storage(const IndexTraits& t) 
                : index_traits_(t) {
            index_ = index_t(t);
        }
        
        void insert(const entry& e) {
            size_t found = 0;
            std::vector<std::string> tmp(index_traits_.attrs.size());
            for(size_t i = 0; i < e.attrs.size(); ++i) {
                for(size_t j = 0; j < tmp.size(); ++j) {
                    if(index_traits_.attrs[j] == e.attrs[i].first) {
                        ++found;
                        tmp[j] = e.attrs[i].second;
                    }
                }
            }
            entry_ptr_t entry_pointer = entry_ptr_t(new entry(e));
            if(found == tmp.size()) {
                IndexTraits tmp_key;
                tmp_key.attrs = tmp;
                index_.insert(std::make_pair(tmp_key, entry_pointer));
            }
            entries_.push_back(entry_pointer);
        }
        
        const index_t& get_index() {
            return index_;
        }
    private:
        index_t index_;
        entry_ptr_vec_t entries_;
        IndexTraits index_traits_;
    };
}

int main() {
    user_info::storage<client::key> stor(client::key{"ip", "id"});
    user_info::entry e1{{"ip", "10.10.10.10"},
                        {"id", "id1"}};
    user_info::entry e2{{"ip", "11.11.11.11"},
                        {"id", "id2"}};
    stor.insert(e1);
    stor.insert(e2);
    
    auto index = stor.get_index();
    auto p = index.find(client::key{"10.10.10.10", "id1"});
    if(p != index.end()) {
        std::cout << "Found!\n";
        for(const auto& s: p->second->attrs)
            std::cout << s.first << ": " << s.second << std::endl;
    } else {
        std::cout << "Not found!\n";
    }
}
