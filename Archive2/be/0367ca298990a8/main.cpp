#include <iterator>
#include <tuple>

struct blockstep_end {};

template<class type, type blockstep, type max>
struct blockstep3_iterator {
    static_assert(max%blockstep==0, "max must be a multiple of blockstep");
    
    typedef std::tuple<type,type,type> value_type;
    typedef std::ptrdiff_t difference_type;
    typedef const std::tuple<type,type,type>* pointer;
    typedef const std::tuple<type,type,type>& reference;
    typedef std::forward_iterator_tag iterator_category;
    
    blockstep3_iterator() :block(), cur() {}    
    blockstep3_iterator(blockstep_end) :block(max,0,0), cur(max,0,0) {}    
    
    blockstep3_iterator& operator++() {
        
        if (++std::get<2>(cur) != std::get<2>(block)+blockstep)
            return *this;
        std::get<2>(cur) = std::get<2>(block);
        
        if (++std::get<1>(cur) != std::get<1>(block)+blockstep)
            return *this;
        std::get<1>(cur) = std::get<1>(block);
        
        if (++std::get<0>(cur) != std::get<0>(block)+blockstep)
            return *this;
        std::get<0>(cur) = std::get<0>(block);
        
        std::get<2>(block)+=blockstep;
        std::get<2>(cur) = std::get<2>(block);
        if (std::get<2>(block) != max)
            return *this;
        std::get<2>(block)=0;
        std::get<2>(cur) = 0;
                
        std::get<1>(block)+=blockstep;
        std::get<1>(cur) = std::get<1>(block);
        if (std::get<1>(block) != max)
            return *this;
        std::get<1>(block)=0;
        std::get<1>(cur) = 0;
                
        std::get<0>(block)+=blockstep;
        std::get<0>(cur) = std::get<0>(block);
        return *this;
    }    
    blockstep3_iterator operator++(int) {
        blockstep3_iterator r(*this);
        operator++();
        return r;
    }
    reference operator*() {return cur;}
    pointer operator->() {return &cur;}
    
    bool operator==(const blockstep3_iterator& rhs) {return cur==rhs.cur;}
    bool operator!=(const blockstep3_iterator& rhs) {return cur!=rhs.cur;}
    friend bool operator==(blockstep_end, const blockstep3_iterator& it) {return it.cur==std::make_pair(max,0,0);}
    friend bool operator!=(blockstep_end, const blockstep3_iterator& it) {return it.cur!=std::make_pair(max,0,0);}
    friend bool operator==(const blockstep3_iterator& it, blockstep_end) {return it.cur==std::make_pair(max,0,0);}
    friend bool operator!=(const blockstep3_iterator& it, blockstep_end) {return it.cur!=std::make_pair(max,0,0);}
private:
    std::tuple<type,type,type> block;
    std::tuple<type,type,type> cur;
};


#include <iostream>
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
                          
    std::cout <<'\n';
    
    int i=0,k=0,j=0;
    blockstep3_iterator<int,BLK,NUM> end = blockstep_end();
    for(blockstep3_iterator<int,BLK,NUM> cur; cur!=end; std::tie(i,k,j) = *++cur)
        std::cout <<i<<','<<k<<','<<j<<'\n';

    return 0;              
}