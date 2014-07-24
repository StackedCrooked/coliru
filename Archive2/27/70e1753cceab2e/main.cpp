#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>


template<typename Iterator>
struct string_view : boost::iterator_range<Iterator> {

   using boost::iterator_range<Iterator>::iterator_range;
   
   void assign(Iterator const b, Iterator const e) {
      *this = {b, e};    
   }
};


template<typename Container, typename Sequence, typename Separator>
auto join(Sequence const& sequence, Separator const& separator) {
   auto first      = std::begin(sequence);
   auto const last = std::end(sequence);
   
   Container result;
   
   if (first != last) {
      boost::push_back(result, *first);
      
      while (++first != last) {
         boost::push_back(result, separator);
         boost::push_back(result, *first);
      }
   }
   
   return result;
}

template<typename Sequence, typename Separator>
auto join(Sequence const& sequence, Separator const& separator) {
   using sequence_value = typename boost::range_value<Sequence>::type;
   
   return join<sequence_value>(sequence, separator);
}

template<template<typename, typename...> class Container, typename ...Args, typename Sequence>
auto copy_range(Sequence const& sequence) {
   using sequence_value = typename boost::range_value<Sequence>::type;
   using container_type = Container<sequence_value, Args...>;
    
   return boost::copy_range<container_type>(sequence);    
}


int main() {
   std::string const text = "you should solve this problem. its easy.";
   
   using separator_type = boost::char_separator<char>;
   using iterator_type  = std::string::const_iterator;
   using value_type     = string_view<iterator_type>;
   using tokenizer_type = boost::tokenizer<separator_type, iterator_type, value_type>;
   
   std::cout << join(
         tokenizer_type(text, separator_type(".")) | boost::adaptors::transformed(
               [] (auto const sentence) {
                     return join<std::string>(
                           copy_range<std::vector>(tokenizer_type(sentence, separator_type(" "))) | boost::adaptors::reversed
                         , " ");
               })
       , ". ") << std::endl;
}
