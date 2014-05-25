#include <boost/asio/error.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

int main()
{
  // Two different error codes.
  boost::system::error_code code1 = make_error_code(
    boost::system::errc::no_such_file_or_directory);
  boost::system::error_code code2 = make_error_code(
    boost::asio::error::host_not_found_try_again);
    
  // That have different error categories.
  assert(code1.category() != code2.category());
  assert(code1.default_error_condition().category() !=
         code2.default_error_condition().category());

  // Yet have the same value.
  assert(code1.value() == code2.value());
  assert(code1.default_error_condition().value() ==
         code2.default_error_condition().value());
  
  // Use the comparision operation to check both value
  // and category.
  assert(code1 != code2);
  assert(code1.default_error_condition() !=
         code2.default_error_condition());
         
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Test with Boost.Filesytem
  try
  {
    boost::filesystem::canonical("bogus_file");
  }
  catch(boost::filesystem::filesystem_error& error)
  {
    if (error.code() == 
        make_error_code(boost::system::errc::no_such_file_or_directory))
    {
      std::cout << "No file or directory" << std::endl;
    }
    if (error.code() ==
        make_error_code(boost::asio::error::host_not_found_try_again))
    {
      std::cout << "Host not found" << std::endl;
    }
  }
}