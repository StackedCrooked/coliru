#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>


std::vector<unsigned> get_data()
{
    std::vector<unsigned> result;
    while (result.size() != 10000000u)
    {
        result.push_back(result.size());
    }
    std::random_shuffle(result.begin(), result.end());
    return result;
}


auto data = get_data();


#ifdef USE_EXCEPTIONS
unsigned process_data()
{
    try
    {
        for (unsigned n : data)
        {
            if (n == data.size()) // never happens
            {
                std::cout << "THROW " << n << std::endl;
                throw n;
            }
        }
        return data.size();
    }
    catch (unsigned n)
    {
        std::cout << "CAUGHT: " << n << std::endl;
        return n;
    }
}
#endif
#ifdef USE_RETURNCODE
unsigned process_data()
{
    unsigned err;
    for (unsigned n : data)
    {
        if (n == data.size()) // never happens
        {
            std::cout << "RETURN " << n << std::endl;
            err = n;
            goto exit;
        }
    }
    return data.size();
    
exit:
    std::cout << "EXIT: " << err;
    return err;
}
#endif


int main()
{   
    typedef std::chrono::high_resolution_clock clock;
    auto begin = clock::now();
    process_data();
    auto elapsed = (clock::now() - begin).count();
    std::cout << elapsed << std::endl;
}