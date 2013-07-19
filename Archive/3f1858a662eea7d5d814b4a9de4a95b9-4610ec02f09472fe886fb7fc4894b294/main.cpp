#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
using namespace boost::multi_index;

struct phonebook_entry
{
  std::string family_name;
  std::string given_name;
  std::string phone_number;

  phonebook_entry(
    std::string family_name, std::string given_name, std::string phone_number):
    family_name(family_name),given_name(given_name),phone_number(phone_number)
  {}
};

// define a multi_index_container with a composite key on
// (family_name,given_name)
typedef multi_index_container<
  phonebook_entry,
  indexed_by<
    //non-unique as some subscribers might have more than one number
    ordered_non_unique< 
      composite_key<
        phonebook_entry,
        member<phonebook_entry,std::string,&phonebook_entry::family_name>,
        member<phonebook_entry,std::string,&phonebook_entry::given_name>
      >
    >,
    ordered_unique< // unique as numbers belong to only one subscriber
      member<phonebook_entry,std::string,&phonebook_entry::phone_number>
    >
  >
> phonebook;

int main() 
{
    phonebook pb; // no initializer_list support for multi_index_container yet
    pb.insert( { "White", "Dorothy", "1" });  
    pb.insert( { "Black", "Dorothy", "2" });  
    pb.insert( { "White", "John",    "3" });  
    pb.insert( { "Black", "John",    "4" });  
    pb.insert( { "White", "Dorothy", "5" });  

   auto const w = pb.equal_range("White");
   auto const d = phonebook_entry{"", "Dorothy", ""};
   auto const wd = std::equal_range(w.first, w.second, d, [](phonebook_entry const& lhs, phonebook_entry const& rhs) {
       return lhs.given_name < rhs.given_name; 
   });
   std::for_each(wd.first, wd.second, [](phonebook_entry const& pbe) { 
       std::cout << pbe.phone_number << "\n"; 
   });
}