    #include <boost/bimap.hpp>
    #include <boost/iterator/transform_iterator.hpp>
    #include <map>
    
    int main(int argc, char const *argv[])
    {
        typedef boost::bimap<int, std::string> BiMapType;
        typedef std::map<int, std::string> MapType;
        typedef std::function<MapType::value_type (const BiMapType::left_value_type&)>
            Transformer;
    
        BiMapType bimap;
        
    
        Transformer transformer_func = [](const BiMapType::left_value_type& elem)
            {
                return std::make_pair(elem.first, elem.second);
            };
    
        auto begin = boost::make_transform_iterator(bimap.left.begin(), transformer_func);
        auto end = boost::make_transform_iterator(bimap.left.end(), transformer_func);
        
        MapType map(begin, end);
        
        return 0;
    }

