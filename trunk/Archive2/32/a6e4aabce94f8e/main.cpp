#include <iterator>
#include <tuple>

template<class type, type blockstep, type max, int count> struct blockstep_tuple;
template<class type, type blockstep, type max> struct blockstep_tuple<type,blockstep,max,1> {
    typedef std::tuple<type> tuptype; 
    static tuptype get_step() {return tuptype(blockstep);}
    static tuptype get_max() {return tuptype(max);}
};
template<class type, type blockstep, type max> struct blockstep_tuple<type,blockstep,max,2> {
    typedef std::tuple<type,type> tuptype; 
    static tuptype get_step() {return tuptype(blockstep,blockstep);}
    static tuptype get_max() {return tuptype(max,0);}
};
template<class type, type blockstep, type max> struct blockstep_tuple<type,blockstep,max,3> {
    typedef std::tuple<type,type,type> tuptype; 
    static tuptype get_step() {return tuptype(blockstep,blockstep,blockstep);}
    static tuptype get_max() {return tuptype(max,0,0);}
};
template<class type, type blockstep, type max> struct blockstep_tuple<type,blockstep,max,4> {
    typedef std::tuple<type,type,type,type> tuptype; 
    static tuptype get_step() {return tuptype(blockstep,blockstep,blockstep,blockstep);}
    static tuptype get_max() {return tuptype(max,0,0,0);}
};
template<class type, type blockstep, type max> struct blockstep_tuple<type,blockstep,max,5> {
    typedef std::tuple<type,type,type,type,type> tuptype; 
    static tuptype get_step() {return tuptype(blockstep,blockstep,blockstep,blockstep,blockstep);}
    static tuptype get_max() {return tuptype(max,0,0,0,0);}
};
template<class type, type blockstep, type max> struct blockstep_tuple<type,blockstep,max,6> {
    typedef std::tuple<type,type,type,type,type,type> tuptype; 
    static tuptype get_step() {return tuptype(blockstep,blockstep,blockstep,blockstep,blockstep,blockstep);}
    static tuptype get_max() {return tuptype(max,0,0,0,0,0);}
};


struct blockstep_end {};

template<class type, type blockstep, type max, int count>
class blockstep_iterator {    
    typedef typename blockstep_tuple<type,blockstep,max,count>::tuptype tuptype;
    tuptype get_step() {return blockstep_tuple<type,blockstep,max,count>::get_step();}
    tuptype get_max() {return blockstep_tuple<type,blockstep,max,count>::get_max();}

    tuptype block;
    tuptype cur;
    
    template<int index> typename std::enable_if<(index<count),bool>::type 
        inc_subblock() {return ++std::get<index>(cur) < std::get<index>(block);}
    template<int index> typename std::enable_if<(index>=count),bool>::type 
        inc_subblock() {return false;}

    template<int index> typename std::enable_if<(index<count),void>::type 
        reset_subblock() {std::get<index>(cur) = std::get<index>(block)-blockstep;}
    template<int index> typename std::enable_if<(index>=count),void>::type 
        reset_subblock() {}

    template<int index> typename std::enable_if<(index<count),bool>::type 
        inc_block() {if (std::get<index>(block)>=max) return false; std::get<index>(cur) = std::get<index>(block); std::get<index>(block)+=blockstep; return true;}
    template<int index> typename std::enable_if<(index>=count),bool>::type 
        inc_block() {return false;}

    template<int index> typename std::enable_if<(index<count),void>::type 
        reset_block() {std::get<index>(block)=blockstep; std::get<index>(cur) = 0;}
    template<int index> typename std::enable_if<(index>=count),void>::type 
        reset_block() {}
            
public:
    static_assert(max%blockstep==0, "max must be a multiple of blockstep");
    
    typedef std::tuple<type,type,type> value_type;
    typedef std::ptrdiff_t difference_type;
    typedef const std::tuple<type,type,type>* pointer;
    typedef const std::tuple<type,type,type>& reference;
    typedef std::forward_iterator_tag iterator_category;
    
    blockstep_iterator() :block(get_step()), cur() {}    
    blockstep_iterator(blockstep_end) :block(get_max()), cur(get_max()) {}    
    
    blockstep_iterator& operator++() {
        if (inc_subblock<5>()) return *this;
        reset_subblock<5>();
        if (inc_subblock<4>()) return *this;
        reset_subblock<4>();
        if (inc_subblock<3>()) return *this;
        reset_subblock<3>();
        if (inc_subblock<2>()) return *this;
        reset_subblock<2>();
        if (inc_subblock<1>()) return *this;
        reset_subblock<1>();
        if (inc_subblock<0>()) return *this;
        reset_subblock<0>();
        
        if (inc_block<5>()) return *this;
        reset_block<5>();
        if (inc_block<4>()) return *this;
        reset_block<4>();
        if (inc_block<3>()) return *this;
        reset_block<3>();
        if (inc_block<2>()) return *this;
        reset_block<2>();
        if (inc_block<1>()) return *this;
        reset_block<1>();
        if (inc_block<0>()) return *this;
        cur = get_max();
        return  *this;
    }
    blockstep_iterator operator++(int) {
        blockstep_iterator r(*this);
        operator++();
        return r;
    }
    reference operator*() {return cur;}
    pointer operator->() {return &cur;}
    
    friend bool operator==(const blockstep_iterator& lhs, const blockstep_iterator& rhs) {return lhs.cur==rhs.cur;}
    friend bool operator!=(const blockstep_iterator& lhs, const blockstep_iterator& rhs) {return lhs.cur!=rhs.cur;}
    friend bool operator==(blockstep_end, const blockstep_iterator& it) {return it.cur==get_max();}
    friend bool operator!=(blockstep_end, const blockstep_iterator& it) {return it.cur!=get_max();}
    friend bool operator==(const blockstep_iterator& it, blockstep_end) {return it.cur==get_max();}
    friend bool operator!=(const blockstep_iterator& it, blockstep_end) {return it.cur!=get_max();}
};


#include <iostream>
#include <cassert>
int main() {
    static const int NUM = 4;
    static const int BLK = 2;
    
    for(int i0=0; i0<NUM; i0+=BLK)
      for(int k0=0; k0<NUM; k0+=BLK)
        for(int j0=0; j0<NUM; j0+=BLK)
          for(int i=i0, ix=i0+BLK; i<ix; ++i)
            for(int k=k0, kx=k0+BLK; k<kx; ++k)
              for(int j=j0, jx=j0+BLK; j<jx; ++j)
                  std::cout <<i<<','<<k<<','<<j<<'\n';
                          
    std::cout <<"===========================================\n";
    
    int i=0,k=0,j=0;
    blockstep_iterator<int,BLK,NUM,3> end = blockstep_end();
    for(blockstep_iterator<int,BLK,NUM,3> cur; cur!=end; std::tie(i,k,j) = *++cur)
        std::cout <<i<<','<<k<<','<<j<<'\n';
                                  
    std::cout <<"===========================================\n";
    
    blockstep_iterator<int,BLK,NUM,3> cur;
    for(int i0=0; i0<NUM; i0+=BLK)
      for(int k0=0; k0<NUM; k0+=BLK)
        for(int j0=0; j0<NUM; j0+=BLK)
          for(int i=i0, ix=i0+BLK; i<ix; ++i)
            for(int k=k0, kx=k0+BLK; k<kx; ++k)
              for(int j=j0, jx=j0+BLK; j<jx; ++j)
                  assert(std::make_tuple(i,k,j)==*cur++);
                  
    std::cout << "identical output";

    return 0;              
}