#include <sstream>
#include <iostream>


inline std::ostringstream::pos_type stream_size(const std::ostringstream& ss)
{
    std::streambuf* buf = ss.rdbuf();
	  
    // Get the current position so we can restore it later
    const std::stringstream::pos_type original = buf->pubseekoff(0, ss.cur, ss.out);

    // Seek to end and get the position
    const std::stringstream::pos_type end = buf->pubseekoff(0, ss.end, ss.out);

    // Restore the position
    buf->pubseekpos(original, ss.out);
    
    return end;
}

int main()
{
    std::ostringstream ss;
    ss << "lolol";
    std::cout << stream_size(ss) << '\n';
    std::cout << ss.rdbuf() << '\n';
}
