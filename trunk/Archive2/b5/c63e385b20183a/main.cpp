#include <sstream>
#include <iostream>


template <typename T>
typename T::pos_type stream_size(const T& strm)
{
    std::streambuf* buf = strm.rdbuf();
	return buf->in_avail();
}

int main()
{
    std::stringstream ss;
    ss << "lolol";
    std::cout << stream_size(ss) << '\n';
}
