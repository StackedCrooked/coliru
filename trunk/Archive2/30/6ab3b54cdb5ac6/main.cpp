// unordered_set::max_load_factor
#include <iostream>
#include <string>
#include <unordered_set>

int main ()
{
  std::unordered_set<std::string> myset =
  {"New York", "Paris", "London", "Hong Kong", "Bangalore", "Tel Aviv", "San Francisco", "San Jose", "Santa Clara", "Mountain View", "Sunnyvale"};

  std::cout << "current max_load_factor: " << myset.max_load_factor() << std::endl;
  std::cout << "current size: " << myset.size() << std::endl;
  std::cout << "current bucket_count: " << myset.bucket_count() << std::endl;
  std::cout << "current load_factor: " << myset.load_factor() << std::endl;

  float z = myset.max_load_factor();
  myset.max_load_factor ( z * 2.0 );
  std::cout << "[max_load_factor doubled]" << std::endl;

  std::cout << "new max_load_factor: " << myset.max_load_factor() << std::endl;
  std::cout << "new size: " << myset.size() << std::endl;
  std::cout << "new bucket_count: " << myset.bucket_count() << std::endl;
  std::cout << "new load_factor: " << myset.load_factor() << std::endl;

  return 0;
}
