#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace unikey
{
    struct nsid_t {}; // namespace id type
    
    void process(nsid_t = {})
    {
        std::cout << "unikey::def" << std::endl;
    }
}


namespace smartkey
{
    struct nsid_t {}; // namespace id type
    
    void process(nsid_t = {})
    {
        std::cout << "smartkey::def" << std::endl;
    }
}


namespace superkey
{
    struct nsid_t {}; // namespace id type
    
    void process(nsid_t = {})
    {
        std::cout << "superkey::def" << std::endl;
    }
}


void initialize() {}
void finalize() {}


template<typename NSID>
void abc_def_ghi(NSID id)
{
    initialize();
    process(id);
    finalize();
}

enum class DongleType
{
    Smart,
    Uni,
};


#ifndef DONGLETYPE
#define DONGLETYPE DongleType::Smart
#endif // DONGLETYPE


template<DongleType> struct DongleTraits;

template<> struct DongleTraits<DongleType::Smart>
{
    typedef smartkey::nsid_t nsid_t;
};

template<> struct DongleTraits<DongleType::Uni>
{
    typedef unikey::nsid_t nsid_t;
};


int main()
{
    {
        abc_def_ghi(unikey::nsid_t());
        abc_def_ghi(smartkey::nsid_t());
        abc_def_ghi(superkey::nsid_t());
    }
    
    {
        typedef typename DongleTraits<DONGLETYPE>::nsid_t nsid_t;
        abc_def_ghi(nsid_t());
        std::cout << "OK" << std::endl;
    }
}