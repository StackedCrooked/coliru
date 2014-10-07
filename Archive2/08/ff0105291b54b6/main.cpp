    #include <boost/range/algorithm.hpp>
    #include <boost/range/metafunctions.hpp>
    #include <boost/range/functions.hpp>
    #include <boost/range/adaptors.hpp>
    #include <boost/range/iterator_range.hpp>
    #include <iostream>
     
    int main(int argc, const char* argv[])
    {
    std::string s = "this is a test";
    auto input_rng
    = boost::make_iterator_range(s.begin(), s.end());
     
    input_rng.size();
    std::cout << "It worked" << std::endl; 
    return 0;
    }
    