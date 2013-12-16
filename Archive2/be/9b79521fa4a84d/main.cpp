//  Copyright (c) 2012 M.A. (Thijs) van den Berg, http://sitmo.com/
//
//  Use, modification and distribution are subject to the MIT Software License.
// (See accompanying file LICENSE.txt or copy at http://www.stdfin.org/LICENSE.txt)

#ifndef STDFIN_RANDOM_THREEFRY_ENGINE_HPP
#define STDFIN_RANDOM_THREEFRY_ENGINE_HPP

#include <stdexcept>

#ifdef __GNUC__
#include <stdint.h>                 // respecting the C99 standard.
#endif
#ifdef _MSC_VER
typedef unsigned __int64 uint64_t;  // Visual Studio 6.0(VC6) and newer..
typedef unsigned __int32 uint32_t;
#endif

// Double mixing function
#define MIX2(x0,x1,rx,z0,z1,rz) \
x0 += x1; \
z0 += z1; \
x1 = (x1 << rx) | (x1 >> (64-rx)); \
z1 = (z1 << rz) | (z1 >> (64-rz)); \
x1 ^= x0; \
z1 ^= z0;


// Double mixing function with key adition
#define MIXK(x0,x1,rx,z0,z1,rz,k0,k1,l0,l1) \
x1 += k1; \
z1 += l1; \
x0 += x1+k0; \
z0 += z1+l0; \
x1 = (x1 << rx) | (x1 >> (64-rx)); \
z1 = (z1 << rz) | (z1 >> (64-rz)); \
x1 ^= x0; \
z1 ^= z0; \


namespace stdfin {
    
    // "req" are requirements as stated in the C++ 11 draft n3242=11-0012
    
    class threefry_engine
    {
    public:
        // req: 26.5.1.3 Uniform random number generator requirements, p.906, table 116, row 1
        typedef uint32_t result_type;
        
        // req: 26.5.1.3 Uniform random number generator requirements, p.906, table 116, row 3
        static result_type (min)() { return 0; }
        
        // req: 26.5.1.3 Uniform random number generator requirements, p.906, table 116, row 4
        static result_type (max)() { return 0xFFFFFFFF; }
        
        // -------------------------------------------------
        // Constructors
        // -------------------------------------------------
        
        // req: 26.5.1.4 Random number engine requirements, p.907 table 117, row 1
        // Creates an engine with the same initial state as all other
        // default-constructed engines of type E.
        threefry_engine() { seed(); }
        
        // req: 26.5.1.4 Random number engine requirements, p.907 table 117, row 2
        // Creates an engine that compares equal to x.
        explicit threefry_engine(const threefry_engine& x)
        {
            for (int i=0; i<4; ++i) _s[i] = x._s[i];
            for (int i=0; i<4; ++i) _k[i] = x._k[i];
            for (int i=0; i<4; ++i) _o[i] = x._o[i];
            _o_counter = x._o_counter;
        }
        
        // req: 26.5.1.4 Random number engine requirements, p.907 table 117, row 3
        // Creates an engine with initial O(size of state) state determined by s.
        explicit threefry_engine(const result_type& s) { seed(s); }
        
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 4
        // Creates an engine with an initial state that depends on a sequence
        // produced by one call to q.generate.
        template<class Seq>
        explicit threefry_engine(Seq& q) { seed(q); }
        
        
        // -------------------------------------------------
        // Seeding
        // -------------------------------------------------
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 5
        void seed()
        {
            _k[0] = 0; _k[1] = 0; _k[2] = 0; _k[3] = 0;
            _s[0] = 0; _s[1] = 0; _s[2] = 0; _s[3] = 0;
            _o_counter = 0;
            
            _o[0] = 0x09218ebde6c85537;
            _o[1] = 0x55941f5266d86105;
            _o[2] = 0x4bd25e16282434dc;
            _o[3] = 0xee29ec846bd2e40b;
        }
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 6
        void seed(const result_type& s)
        {
            _k[0] = s; _k[1] = 0; _k[2] = 0; _k[3] = 0;
            _s[0] = 0; _s[1] = 0; _s[2] = 0; _s[3] = 0;
            _o_counter = 0;
            encrypt_counter();
            
        }
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 7
        template<class Sseq>
        void seed(Sseq& q)
        {
            typename Sseq::result_type w[8];
            q.genarate(&w[0], &w[8]);
            for (int i=0; i<4; ++i)
                _k[i] = (w[2*i] << 32) | w[2*i+1];
            _o_counter = 0;
            encrypt_counter();
        }
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 8
        // Advances e’s state ei to ei+1 = TA(ei) and returns GA(ei).
        uint32_t operator()()
        {
            if (_o_counter < 8) {
                short _o_index = _o_counter >> 1;
                _o_counter++;
                if (_o_counter&1)
                    return _o[_o_index];
                else
                    return _o[_o_index] >> 32;
            }
            inc_counter();
            encrypt_counter();
            _o_counter = 1; // the next call
            return _o[0];   // this call
        }
        
        // -------------------------------------------------
        // misc
        // -------------------------------------------------
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 9
        // Advances e’s state ei to ei+z by any means equivalent to z
        // consecutive calls e().
        void discard(uint64_t z)
        {
            // detect bit overflow, and process those
            if (z >= (0xFFFFFFFFFFFFFFFF - _s[0]) ) {
                ++_s[1];
                if (_s[1] == 0) {
                    ++_s[2];
                    if (_s[2] == 0) {
                        ++_s[3];
                    }
                }
            }
            
            // add it
            _s[0] += z;
            
            _o_counter = 0;
            encrypt_counter();
        }
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 10
        // This operator is an equivalence relation. With Sx and Sy as the infinite
        // sequences of values that would be generated by repeated future calls to
        // x() and y(), respectively, returns true if Sx = Sy; else returns false.
        bool operator==(const threefry_engine& y)
        {
            if (_o_counter != y._o_counter) return false;
            for (int i=0; i<4; ++i) {
                if (_s[i] != y._s[i]) return false;
                if (_k[i] != y._k[i]) return false;
                if (_o[i] != y._o[i]) return false;
            }
            return true;
        }
        
        // req: 26.5.1.4 Random number engine requirements, p.908 table 117, row 11
        bool operator!=(const threefry_engine& y) { return !(*this == y); }
        
        
        // Extra function to set the key
        void set_key(uint64_t k0=0, uint64_t k1=0, uint64_t k2=0, uint64_t k3=0)
        {
            _k[0] = k0; _k[1] = k1; _k[2] = k2; _k[3] = k3;
            _o_counter = 0;
            encrypt_counter();
        }
        
        // set the counter
        void set_counter(uint64_t s0=0, uint64_t s1=0, uint64_t s2=0, uint64_t s3=0)
        {
            _s[0] = s0; _s[1] = s1; _s[2] = s2; _s[3] = s3;
            _o_counter = 0;
            encrypt_counter();
        }
        
        
        
        
    private:
        void encrypt_counter()
        {
            uint64_t b[4];
            uint64_t k[5];
            
            for (int i=0; i<4; ++i) b[i] = _s[i];
            for (int i=0; i<4; ++i) k[i] = _k[i];
            
            k[4] = 0x1BD11BDAA9FC1A22 ^ k[0] ^ k[1] ^ k[2] ^ k[3];
            
            MIXK(b[0], b[1], 14,   b[2], b[3], 16,   k[0], k[1], k[2], k[3]);
            MIX2(b[0], b[3], 52,   b[2], b[1], 57);
            MIX2(b[0], b[1], 23,   b[2], b[3], 40);
            MIX2(b[0], b[3],  5,   b[2], b[1], 37);
            MIXK(b[0], b[1], 25,   b[2], b[3], 33,   k[1], k[2], k[3], k[4]+1);
            MIX2(b[0], b[3], 46,   b[2], b[1], 12);
            MIX2(b[0], b[1], 58,   b[2], b[3], 22);
            MIX2(b[0], b[3], 32,   b[2], b[1], 32);
            
            MIXK(b[0], b[1], 14,   b[2], b[3], 16,   k[2], k[3], k[4], k[0]+2);
            MIX2(b[0], b[3], 52,   b[2], b[1], 57);
            MIX2(b[0], b[1], 23,   b[2], b[3], 40);
            MIX2(b[0], b[3],  5,   b[2], b[1], 37);
            MIXK(b[0], b[1], 25,   b[2], b[3], 33,   k[3], k[4], k[0], k[1]+3);
            
            MIX2(b[0], b[3], 46,   b[2], b[1], 12);
            MIX2(b[0], b[1], 58,   b[2], b[3], 22);
            MIX2(b[0], b[3], 32,   b[2], b[1], 32);
            
            MIXK(b[0], b[1], 14,   b[2], b[3], 16,   k[4], k[0], k[1], k[2]+4);
            MIX2(b[0], b[3], 52,   b[2], b[1], 57);
            MIX2(b[0], b[1], 23,   b[2], b[3], 40);
            MIX2(b[0], b[3],  5,   b[2], b[1], 37);
            
            for (int i=0; i<4; ++i) _o[i] = b[i] + k[i];
            _o[3] += 5;
        }
        
        void inc_counter()
        {
            ++_s[0];
            if (_s[0] == 0) {
                ++_s[1];
                if (_s[1] == 0) {
                    ++_s[2];
                    if (_s[2] == 0) {
                        ++_s[3];
                    }
                }
            }
        }
        
        
    private:
        
        uint64_t _k[4]; // key
        uint64_t _s[4]; // state (counter)
        uint64_t _o[4]; // cipher output
        
        short _o_counter; // 
    };
    
} // namespace stdfin

#undef MIXK
#undef MIX2

#endif
