#include <iostream>
#include <string>

#define TOKENIZE 1
#define SCAN     2

/**
 * A ToPTrace header is a line in which each tab-delimited token ends in a
 * '#' character. This function returns true if the given string matches
 * this condition. %line should contain no trailing newline: a valid header
 * has '#' as its final character.
 */

#if APPROACH == TOKENIZE

    #include <vector>
    #include <sstream>
    
    std::vector<std::string> tokenize(const std::string& str, const char delimiter, bool collapse_delimiters)
    {
        std::vector<std::string> tokens;
        
    	std::stringstream ss(str);
    	std::string tmp;
    	while (std::getline(ss, tmp, delimiter)) {
    		if (!tmp.empty() || !collapse_delimiters)
    			tokens.push_back(tmp);
    	}
    	
    	return tokens;
    }
    
    bool looksLikeHeader(const std::string& line)
    {
        const std::vector<std::string> tokens = tokenize(line, '\t', false);
    	std::vector<std::string>::const_iterator it = tokens.begin(), end = tokens.end();
    	for ( ; it != end; ++it) {
    		const std::string& str = *it;
    		if (str.empty() || *str.rbegin() != '#')
    			return false;
    	}
        
    	return true;
    }
    
#elif APPROACH == SCAN
    
    bool looksLikeHeader(const std::string& line)
    {
        if (line.empty())
            return false;
        
        size_t pos = 0;
        while (true) {
            pos = line.find('\t', pos+1);
            
            if (pos == std::string::npos)
                return (*line.rbegin() == '#');
            
            if (line[pos-1] != '#')
                return false;
        }
        
        return true;
    }
#endif

int main()
{
    std::cout << looksLikeHeader("lol\tok") << looksLikeHeader("lol#\tok") << looksLikeHeader("lol#\tok#") << '\n';
    for (size_t i = 0; i < N; i++) {
        (void)looksLikeHeader("lol\tok");
        (void)looksLikeHeader("lol#\tok");
        (void)looksLikeHeader("lol#\tok#");
    }
}
