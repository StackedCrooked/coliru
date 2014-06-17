#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace {
    
    class token_iterator : public std::iterator<std::forward_iterator_tag, std::string> {
    public:
        static token_iterator const empty;
        
        token_iterator(void): 
            _position(std::string::npos),
            _source(""),
            _delimeter("")
        {
        }
        
        token_iterator(std::string const& source, std::string const& delimeter):
            _position(0),
            _source(source),
            _delimeter(delimeter)
        {
            next();
        }
        
        token_iterator(token_iterator const& original):
            _position(original._position),
            _current(original._current),
            _source(original._source),
            _delimeter(original._delimeter)
        {
        }
        
        token_iterator(token_iterator&& original):
            _position(std::move(original._position)),
            _current(std::move(original._current)),
            _source(original._source),
            _delimeter((original._delimeter))
        {
        }
        
        token_iterator& operator++(void) {
            next();
            return *this;
        }
        
        token_iterator operator++(int) {
            token_iterator retv = *this;
            next();
            
            return std::move(retv);
        }
        
        std::string const& operator* (void) const {
            return _current;
        }
        
        bool operator== (token_iterator const& other) {
            if (_position == std::string::npos) {
                return other._position == std::string::npos;
            }
            return _position  == other._position &&
                   _source    == other._source   &&
                   _delimeter == other._delimeter;
        }
        
        bool operator!= (token_iterator const& other) {
            return !(*this == other);
        }
        
    private:
        typename std::string::size_type _position;
        std::string        _current;
        std::string const& _source;
        std::string const& _delimeter;
        
        void next(void) {
            if (_position == std::string::npos) {
                return;
            }
            if (_position >= _source.size()) {
                _position = std::string::npos;
                _current  = "";
                return;
            }
            if (_delimeter.size() == 0) {
                _current   = _source.substr(_position, 1);
                _position += 1;
                return;
            }
            
            auto begin = _position;
            auto end   = _source.find(_delimeter, begin);
            if (end == std::string::npos) {
                _position = _source.size();
                _current  = _source.substr(begin);
            }
            else {
                _position = end + _delimeter.size();
                _current  = _source.substr(begin, end - begin);
            }
        }
    };
    
    token_iterator const token_iterator::empty;
    
    class token_range {
    public:
        token_range(std::string const& source, std::string const& delimeter):
            _source(source),
            _delimeter(delimeter)
        {
        }
        
        token_range(std::string const& source, std::string&& delimeter):
            _source(source),
            _delimeter(delimeter)
        {
        }
        
        token_range(std::string&& source, std::string const& delimeter):
            _source(source),
            _delimeter(delimeter)
        {
        }
        
        token_range(std::string&& source, std::string&& delimeter):
            _source(source),
            _delimeter(delimeter)
        {
        }
        
        token_iterator begin(void) const {
            return token_iterator(_source, _delimeter);
        }
        
        token_iterator const& end(void) const {
            return token_iterator::empty;
        }
        
    private:
        std::string const _source;
        std::string const _delimeter;
    };
    
    std::pair<std::string, std::string> split(std::string const& source, std::string const& delimeter) {
        auto pos = source.find(delimeter);
        if (pos == std::string::npos) {
            return std::make_pair(source, std::string());
        }
        return std::make_pair(source.substr(0, pos), source.substr(pos + delimeter.size()));
    }
}


typedef std::pair<std::string, std::string> parameter_value;

std::map<std::string, std::vector<parameter_value>> parse_parameters(std::string const& s) {
    std::map<std::string, std::vector<parameter_value>> retv;
    
    for (auto item : token_range(s, "&")) {
        auto keyval = split(item, "=");
        
        for (auto val : token_range(keyval.second, ",")) {
            retv[keyval.first].push_back(split(val, ".."));
        }
    }
    
    return retv;
}

int main()
{
    for (auto pair : parse_parameters("id=0..100,100..200&limit=255&page=1")) {
        auto name = pair.first;
        
        std::cout << name << " = [" << std::endl;
        for (auto value : pair.second) {
            auto is_range = value.second.size() > 0;
            
            if (is_range) {
                std::cout << "\t(" << value.first << ", " << value.second << ")" << std::endl;
            }
            else {
                std::cout << "\t" << value.first << std::endl;
            }
        }
        std::cout << "]" << std::endl;
    }
}
