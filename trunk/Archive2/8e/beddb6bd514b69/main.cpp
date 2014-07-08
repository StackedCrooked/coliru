#include <functional>
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/algorithm/string.hpp>

int main()
{
      // These can be comma delimited
      //   ex. <mapped_vars>@TestTable[TestColumn], @TestTable[TestColumn2]</mapped_vars>
      std::string value = "@TestTable[TestColumn], @TestTable[TestColumn2]";
      std::vector<std::string> splitList;
      boost::split(splitList, value, boost::is_any_of(",@"), boost::token_compress_off);
      std::for_each(splitList.begin(), splitList.end(), [](std::string& zVar) { std::cout << "Value: " << zVar << std::endl; });
}