#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <algorithm>

#include <boost/thread/future.hpp>
#include <boost/bind.hpp>

int parallel_sum(int value, int size)
{
  int sum = 0;
  if ( size < 1440 )
    for ( int i = 0; i < size; ++i )
      sum += value;
  else {
    auto handle = boost::async(boost::launch::async, boost::bind(parallel_sum, value, size-size/2));
    sum += parallel_sum(value, size/2);
    sum += handle.get();
  }
  return sum;
}

int main(int argc, char* argv[])
{
    std::cout << parallel_sum(1, 500) << std::endl;
	return 0;
}
