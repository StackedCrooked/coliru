#include <sstream>
#include <iostream>


template <typename T>
typename T::pos_type stream_size(const T& strm)
{
    std::streambuf* buf = strm.rdbuf();
	const typename T::pos_type size = buf->pubseekoff(0, strm.end, ios_base::out);
	buf->pubseekpos(0);
	
	return size;
}

int main()
{
    std::ostringstream ss;
    ss << "lolol";
    std::cout << stream_size(ss) << '\n';
}