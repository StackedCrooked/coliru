#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace unikey
{
    struct id {}; // namespace id
    
    void process(id = {})
    {
        std::cout << "unikey::def" << std::endl;
    }
}


namespace smartkey
{
    struct id {}; // namespace id
    
    void process(id = {})
    {
        std::cout << "unikey::def" << std::endl;
    }
}


void initialize() {}
void finalize() {}


template<typename NSID>
void abc_def_ghi(NSID nsid)
{
    initialize();
    process(nsid);
    finalize();
}

enum class DongleType
{
    Smart,
    Uni,
};


#ifndef DONGLETYPE
#define DONGLETYPE DongleType_Smart
#endif // DONGLETYPE


template<DongleType> struct DongleTraits;

template<> struct DongleTraits<DongleType::Smart>
{
    typedef smartkey::id nsid_t;
};

template<> struct DongleTraits<DongleType::Uni>
{
    typedef unikey::id nsid_t;
};


int main()
{
    typedef typename DongleTraits<DONGLETYPE>::nsid_t nsid_t;
    abc_def_ghi(nsid_t());
}