template<typename Iterator, typename Delimiter>
std::string rangeToString(Iterator begin, Iterator end, Delimiter prefix, Delimiter suffix, Delimiter separator)
{
        std::stringstream ss;

        ss << prefix;
        for(auto it = begin; it != end; it++)
        {
                ss << *it;

                // Replaced it + 1 with this to allow bidir and forward iterators
                if(std::next(it) != end)
                        ss << separator;
        }
        ss << suffix;

        return ss.str();
}
