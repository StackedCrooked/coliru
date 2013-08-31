//http://en.wikipedia.org/wiki/Jenkins_hash_function
//unused except for validation
unsigned hash_string(const char * s) {
    unsigned hash = 0;
    for(; *s; ++s) {          //0
        hash += *s;           //1
        hash += (hash << 10); //2
    	hash ^= (hash >> 6);  //3
    }
    hash += (hash << 3);      //4
    hash ^= (hash >> 11);     //5
    hash += (hash << 15);     //6
    return hash;
}

//constexpr version
//after inlining, states 0-3 are "recursive", but should be tail recursive.  4-6 are not recursive.
template<unsigned caseval=0> 
constexpr unsigned strHash(char const* in, unsigned hash=0) {
    return
      caseval==0 ? *in ? strHash<1>(in,hash) : strHash<4>(in,hash)
    : caseval==1 ? strHash<2>(in,hash+*in)
    : caseval==2 ? strHash<3>(in,hash+(hash<<10))
    : caseval==3 ? strHash<0>(in+1,hash^(hash>>6))
    : caseval==4 ? strHash<5>(in,hash+(hash<<3))
    : caseval==5 ? strHash<6>(in,hash^(hash>>11))
    : caseval==6 ? hash+(hash<<15)
    : hash; //error condition: abort
}

#include <iostream>
int main() {
    std::cout << hash_string("") << ' ' << strHash("") << '\n';
    std::cout << hash_string("a") << ' ' << strHash("a") << '\n';
    std::cout << hash_string("Z") << ' ' << strHash("Z") << '\n';
    std::cout << hash_string("aZ") << ' ' << strHash("aZ") << '\n';
    std::cout << hash_string("Za") << ' ' << strHash("Za") << '\n';    
    
    std::string input = "Steve"; //force a run time string 
    switch(strHash(input.c_str())) {
    case strHash("Bob"): std::cout << "Bob"; break;
    case strHash("Steve"): std::cout << "Steve"; break;
    case strHash("Ted"): std::cout << "Ted"; break;
    default: std::cout << "OMG ERROR"; break;
    }
}
