#include <string>
#include <iostream>


struct HTTPParseError : virtual std::exception
{
    
};


struct Header
{
    std::string key, value;
};


Header ParseHeader(const char* begin, const char* end)
{
    enum State
    {
        Initial,
        Key,
        Space,
        Value
    };

    State state = Initial;

    const char* valueBegin = nullptr;

    Header result;
    const char* i = begin;

    for (; i != end; ++i)
    {
        char c = *i;

        switch (state)
        {
            case Initial: switch (c)
            {
                case ' ': case ':': throw HTTPParseError();
                default: state = Key; continue;
            }
            case Key: switch (c)
            {
                case ' ': throw HTTPParseError();
                case ':': state = Space; result.key.assign(begin, i); continue;
                default : continue;
            }
            case Space: switch (c)
            {
                case ' ': continue; // multiple spaces are allowed
                case ':': throw HTTPParseError();
                default : valueBegin = i; state = Value; continue;
            }
            case Value: switch (c)
            {
                case ':': throw HTTPParseError();
                default : continue;
            }
        }
    }

    // end of string = end of header value
    result.value.assign(valueBegin, i);
    return result;
}


int main()
{
    std::string line = "Content-Length: 123";
    Header header = ParseHeader(&*line.begin(), &*line.end());
    std::cout << "key=[" << header.key << "] value=[" << header.value << "]" << std::endl;
}

