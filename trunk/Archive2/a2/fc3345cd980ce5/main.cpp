#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
#include <vector>
#include <sstream>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/sha1.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>




std::string to_base64(const std::vector<unsigned char>& data)
{
    using namespace boost::archive::iterators;

	typedef
		insert_linebreaks<         // insert line breaks every 72 characters
		base64_from_binary<    // convert binary values ot base64 characters
		transform_width<   // retrieve 6 bit integers from a sequence of 8 bit bytes
		const char *,
		6,
		8
		>
		>
		, 72
		>
		base64_iterator;

	std::vector<unsigned char> buff(data);
	size_t number_of_padd_chars = (buff.size() % 3 != 0) ? 3 - (buff.size() % 3) : 0;
	buff.insert(buff.end(), number_of_padd_chars, '\0');

	base64_iterator begin(&buff[0]), end(&buff[0] + data.size());
	std::string result(begin, end);
	result.insert(result.end(), number_of_padd_chars, '=');

	return result;
}

std::string to_base64(const std::string& data)
{
    std::vector<uint8_t> datav(data.begin(), data.end());
	return to_base64(datav);
}

int main()
{
  std::cout << to_base64("hello");
}


