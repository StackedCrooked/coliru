#include <vector>


std::vector<unsigned> get_data();
std::vector<unsigned>::size_type get_size();



unsigned process_data()
{
    #ifndef USE_EXCEPTIONS
    int err;
    #endif
    for (std::vector<unsigned>::size_type i = 0; i != get_data().size(); ++i)
    {
        for (std::vector<unsigned>::size_type j = 0; j != get_data().size(); ++j)
        {
            if (i == get_data().size() && (i + j) < 2*get_size())
            {
                #ifdef USE_EXCEPTIONS
                throw get_data().size();
                #else
                int err = get_data().size();
                goto error;
                #endif
            }   
        }
    }
    return get_size();
    
    #ifndef USE_EXCEPTIONS
    error:
        return err;
    #endif
}

int main()
{   
    try
    {
        process_data();
        return 0;
    }
    catch (unsigned n)
    {
        return n;
    }
}