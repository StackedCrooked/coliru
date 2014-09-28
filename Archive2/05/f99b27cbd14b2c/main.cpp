#include <iostream>

struct error
{
    virtual ~error() = default ;
    virtual int code() const = 0 ;
};

template < typename DERIVED > struct error_helper : error
{
    virtual int code() const override { return DERIVED::error_code() ; }
};

struct download_error : error_helper<download_error>
{
    static int error_code() { return 1 ; }
};

struct upload_error : error_helper<upload_error>
{
    static int error_code() { return 6 ; }
};

int main()
{
    download_error de ;
    upload_error ue ;
    error* errors[] = { &de, &ue } ;
    for( error* e : errors ) std::cout << e->code() << ' ' ;
}
