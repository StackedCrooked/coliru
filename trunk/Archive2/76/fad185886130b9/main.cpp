#include <sstream>
#include <iostream>


template <typename T>
typename T::pos_type stream_size(const T& strm)
{
    std::streambuf* buf = strm.rdbuf();
	const std::streampos orig = buf->pubseekpos(0);
	const typename T::pos_type size = buf->pubseekoff(0, strm.end);
	buf->pubseekpos(orig);
	
	return size;
}

int main()
{
    std::stringstream ss;
    ss << "lolol";
    std::cout << stream_size(ss) << '\n';
}
