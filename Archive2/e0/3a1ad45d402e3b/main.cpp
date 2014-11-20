#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <cassert>

namespace user_info {
    struct key;
    
    class comparable {
    public:
        virtual bool less(const key& l, 
                          const key& r) const = 0;
    };

    struct key {
        key(const key& other) : attrs(other.attrs) {}
        key(const std::initializer_list<std::string>& l) : attrs(l) {}
        key(const std::vector<std::string>& l) : attrs(l){}            
        std::vector<std::string> attrs;
    };
    
    struct key_compare {
//        key_compare() {}
        key_compare(std::shared_ptr<comparable> c) : comp(c) {}
        bool operator()(const key& l, const key& r) {
            assert(comp);
            return comp->less(l.attrs, r.attrs);
        }
        std::shared_ptr<user_info::comparable> comp;
    };
    
}

namespace client {
    struct ip_id_comparator : public user_info::comparable {
        bool less(const user_info::key& l, 
                  const user_info::key& r) const override {
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
    
    class storage {
    public:
        typedef std::map<key, entry_ptr_t, key_compare> index_t;
    public:
        storage(const key_compare& c, const key& k) 
                : index_traits_(c),
                  key_(k),
                  index_(c) {
        }
        
        void insert(const entry& e) {
            size_t found = 0;
            std::vector<std::string> tmp(key_.attrs.size());
            for(size_t i = 0; i < e.attrs.size(); ++i) {
                for(size_t j = 0; j < key_.attrs.size(); ++j) {
                    if(key_.attrs[j] == e.attrs[i].first) {
                        ++found;
                        tmp[j] = e.attrs[i].second;
                    }
                }
            }
            entry_ptr_t entry_pointer = entry_ptr_t(new entry(e));
            if(found == tmp.size()) {
                key tmp_key(tmp);
                index_.insert(std::make_pair(tmp_key, entry_pointer));
            }
            entries_.push_back(entry_pointer);
        }
        
        const index_t& get_index() {
            return index_;
        }
    private:
        entry_ptr_vec_t entries_;
        key_compare index_traits_;
        key key_;
        index_t index_;
    };
}

int main() {
    user_info::storage stor(user_info::key_compare(std::make_shared<client::ip_id_comparator>()),
                            user_info::key({"ip", "id"}));
    user_info::entry e1{{"ip", "10.10.10.10"},
                        {"id", "id1"}};
    user_info::entry e2{{"ip", "11.11.11.11"},
                        {"id", "id2"}};
    stor.insert(e1);
    stor.insert(e2);    
    auto index = stor.get_index();
    auto p = index.find(user_info::key{"10.10.10.10", "id1"});
    if(p != index.end()) {
        std::cout << "Found!\n";
        for(const auto& s: p->second->attrs)
            std::cout << s.first << ": " << s.second << std::endl;
    } else {
        std::cout << "Not found!\n";
    }
}
