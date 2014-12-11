#include <sstream>
#include <iostream>


inline std::ostringstream::pos_type stream_size(const std::ostringstream& strm)
{
    std::streambuf* buf = strm.rdbuf();
	return buf->pubseekoff(0, strm.end, strm.out);
}

int main()
{
    std::ostringstream ss;
    ss << "lolol";
    std::cout << stream_size(ss) << '\n';
    std::cout << ss.rdbuf() << '\n';
}
