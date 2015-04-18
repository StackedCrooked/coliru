#include <iostream>
#include <unordered_map>
#include <string>
#include <atomic>
#include <vector>
#include <tuple>

template <typename T>
struct scoped_increment {
    T& t;
    scoped_increment(T& t) : t{t} { ++t; }
    ~scoped_increment() { --t; }
};


struct wait_if_not_available{};
struct throw_if_not_available{};


struct physics_entity_data { int x{44}; };
struct physics_debug_data  { int y{55}; };


template <typename T>
struct data_wrapper {
    
    T data_;
    
    std::atomic_int active_writer_{0};
    std::atomic_int active_reader_{0};
    
};


template <typename C>
struct read_access { 
    store_wrapper<C>& store_;
    scoped_increment<C>
    
    read_access(store_wrapper<C>& store_) : store_{store_} { ++store_.active_reader_; } 
      
};
    

template <typename ...Ts>
struct data_store : data_wrapper<Ts>... {
        
    data_store() {}
    data_store(Ts&&... ts) : data_wrapper<Ts>{ts}... {}
    
    
    template <typename C>
    struct write_access{ store_wrapper<C>& store_; };
    
     
    template <typename C>
    friend
    read_access<C> make_reader(data_store<Ts...>& d, C) { return {static_cast<C&>(d)}; }
        
};




int main() {
    
    data_store< physics_entity_data, 
                physics_debug_data  > data_;
    
    auto f = make_reader(data_,physics_debug_data{});
    
    std::cout << f.data_.y;
        
}
