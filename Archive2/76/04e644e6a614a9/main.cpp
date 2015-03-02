#include <iostream>
#include <stdexcept>
#include <vector>

class Manchester
{
public:

    static std::vector<unsigned> encode(const std::vector<unsigned>& data, unsigned length)
    {
        std::vector<unsigned> output(length * 2);
    
        for (unsigned i = 0; i < length; i++)
        {
    
            // Work out the array indexes to use
            unsigned bid = i * 2;
            unsigned nbid = bid + 1;
    
            // Get the data
            unsigned real = data[i];
    
            unsigned bit = 0;
            unsigned nbit = 0;
    
            // Work out what it is
            if (real == 0)
            {
                bit = (ZERO >> 1) & 1;
                nbit = ZERO & 1;
            }
            else // real == 1
            {
                bit = (ONE >> 1) & 1;
                nbit = ONE & 1;
            }
    
            #ifndef NDEBUG
                std::cout << "[encode] " << real << " [" << bit << nbit << "]" << std::endl;
            #endif
    
            output[bid] = bit;
            output[nbid] = nbit;
        }
    
        return output;
    }
    
    static std::vector<unsigned> decode(const std::vector<unsigned>& data, unsigned length)
    {
        if ((length % 2) != 0)
        {
            throw std::range_error("length is not a multiple of 2");
        }
        
        std::vector<unsigned> output(length / 2);
    
        for (unsigned i = 0; i < (length / 2); i++)
        {
            // Work out the array indexes to use
            unsigned bid = i * 2;
            unsigned nbid = bid + 1;
    
            // Get the data
            unsigned bit = data[bid];
            unsigned nbit = data[nbid];
    
            // Put the data into an unsigned int
            unsigned sbit = (bit << 1) | nbit;
    
            // Check only for MANCHESTER_ONE,
            // assuming that it will be equal
            // to MANCHESTER_ZERO if not
            unsigned real = unsigned(sbit == ONE);
    
            #ifndef NDEBUG
                std::cout << "[decode] bit: " << bit << nbit << " [" << real << "]" << std::endl;
            #endif
    
            output[i] = real;   
        }
        return output;
    }
    
private:

    static const unsigned ONE;
    static const unsigned ZERO;
};

const unsigned Manchester::ONE = 1u;
const unsigned Manchester::ZERO = 2u;


int main()
{
    typedef std::vector<unsigned> vec_t;
    
     // Some unencoded data
    unsigned data[] = { 1u, 1u, 0u, 0u };
    // Initialize vector with array
    vec_t vec(data, data+sizeof(data) / sizeof(unsigned));
    
    vec_t encoded = Manchester::encode(vec, 4);
    vec_t decoded = Manchester::decode(encoded, 8);
}