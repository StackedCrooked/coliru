//////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2014 John Gilson
//
// File Name     : CharPermutationRank.cpp
// Version       : $Revision$
// Library       : 
// Project       : 
// Author        : John Gilson (Email: jag@acm.org)
// Others        : 
// Created       : 2014/04/06 10:25:10 Pacific Daylight Time
// Last Modified : $Date$ by $Author$
// Description   : 
//
//////////////////////////////////////////////////////////////////////

/*

Original problem

Consider a "word" as any sequence of capital letters A-Z (not limited
to just "dictionary words"). For any word with at least two different
letters, there are other words composed of the same letters but in a
different order (for instance, STATIONARILY/ANTIROYALIST, which happen
to both be dictionary words; for our purposes "AAIILNORSTTY" is also a
"word" composed of the same letters as these two).

We can then assign a number to every word, based on where it falls in
an alphabetically sorted list of all words made up of the same set of
letters. One way to do this would be to generate the entire list of
words and find the desired one, but this would be slow if the word is
long.

Write a program which takes a word as a command line argument and
prints to standard output its number. Do not use the method above of
generating the entire list. Your program should be able to accept any
word 25 letters or less in length (possibly with some letters
repeated), and should use no more than 1 GB of memory and take no more
than 500 milliseconds to run. Any answer we check will fit in a 64-bit
integer.

Sample words, with their rank:

ABAB = 2
AAAB = 1
BAAA = 4
QUESTION = 24572
BOOKKEEPER = 10743

*/

/*

My solution meets, and exceeds, the above requirements:

- A character interval can be chosen, that is, the uppercase character
  interval is not hardwired into this solution.  A lowercase interval
  and a digits interval are also provided.

- The character string passed in as a command line argument and used
  to conceptually "generate" all of the permutations need not be the
  character string used to find rank.  And the character string used
  to find rank need not even be one of the permutations.

- Rank is found with respect to a string order of the permutations.
  In the original problem this is assumed to be standard alphabetical
  order.  This code allows for both standard alphabetical order and
  reverse alphabetical order.

- The main function below is invoked as described in the problem
  statement but the interaction is a bit richer to use this greater
  functionality.

- Its time/space complexity is excellent while defining useful
  abstractions modularly.

The code is written in C++11, the latest ISO Standard C++ accepted in
2011.  To make you must have a recent version of gcc (I used version
4.8.2).  One can then make simply with:

g++ -std=c++11 -O3 -o rank CharPermutationRank.cpp

*/

// Standard C++ Library headers
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

// Permutation counting and factorial go together like peanut butter
// and jelly.
//
// n! = 1 if 0 <= n <= 1
// n! = n * (n - 1)! if n > 1
// n! = undefined if n < 0
//
// And the number of ways to permute n elements, with no repetitions,
// is n!

inline std::uintmax_t factorial(int n)
{
  if (n < 0)
    throw std::out_of_range("Factorial not defined for a negative integer.");
  std::uintmax_t result(1);
  for(int counter = 1; counter <= n; ++counter)
    result *= counter;
  return(result);
}

// We will permute the characters that comprise a "word" and those
// characters will be drawn from a character interval.  A character
// interval is defined by all characters from first char to last char,
// inclusive.  If the last char comes before the first char then the
// interval is empty.  Note that a char interval is defined
// statically, i.e., at compile-time.

template<char First, char Last = First>
struct CharInterval
{
  static constexpr char FirstChar = First;
  static constexpr char LastChar = Last;
  // std::uint_fast16_t is the fastest unsigned integer type with
  // width of at least 16 bits
  using SizeType = std::uint_fast16_t; // type used for interval size
  static constexpr bool IsEmpty = (LastChar < FirstChar);
  static constexpr SizeType Size =
    (FirstChar <= LastChar ? LastChar - FirstChar + 1 : 0);
  static constexpr bool isValid(char c)
  {
    return(c >= FirstChar && c <= LastChar);
  }
  // A string representation of the char interval
  static const std::string & toString()
  {
    static const std::string s =
      std::string(1, '[') +
      FirstChar +
      ", " +
      LastChar +
      ']';
    return(s);
  }
  // Zero-based position of a char in the char interval
  static constexpr SizeType getIndex(char c)
  {
    return(isValid(c) ? c - FirstChar :
           throw std::out_of_range("Char not in interval " +
                                   toString() +
                                   ": " +
                                   c));
  }
  // If the char is valid in the char interval then return.  If not,
  // attempt lowercase-to-uppercase or uppercase-to-lowercase
  // conversion and return if valid in the char interval.
  static char toValid(char c)
  {
    if (isValid(c))
      return(c);
    else if (std::islower(c))
    {
      const char cu = std::toupper(c);
      if (isValid(cu))
        return(cu);
    }
    else if (std::isupper(c))
    {
      const char cl = std::tolower(c);
      if (isValid(cl))
        return(cl);
    }
    throw std::out_of_range("Char invalid and inconvertible"
                            " to valid char in interval " +
                            toString() +
                            ": " +
                            c);
  }
};

// Define various char intervals

// Interval of all uppercase letters
using UppercaseInterval = CharInterval<'A', 'Z'>;

// Interval of all lowercase letters
using LowercaseInterval = CharInterval<'a', 'z'>;

// Interval of all digits
using DigitInterval = CharInterval<'0', '9'>;

// Determine the rank of any character string S1 in an ordering of the
// permutations of a character string S2.  Note that S1 can be
// completely unrelated to S2, that is, S1 and S2 need not be equal
// and S1 need not be a permutation of S2.  The rank can be found in a
// standard alphabetical ordering of the permutations of S2 or in a
// reverse alphabetical ordering.
//
// The parameterized type is the char interval type

template<typename CharIntervalT>
class CharPermutationRank
{
public:
  // Type declarations
  using CharIntervalType = CharIntervalT;
  using CharOccurrenceType = std::uint_fast16_t;
  // An array to hold the occurrence count of each char in the char
  // interval.  std::array was introduced in C++11.
  using AllCharOccurrencesType = std::array<CharOccurrenceType,
                                            CharIntervalType::Size>;
  using RankType = std::uintmax_t;

  // The kinds of ordering of the permutations
  enum LexicographicOrder {StandardOrder, ReverseOrder};

  CharPermutationRank()
    : occurrences()
  {}
  // A range of chars specified by a pair of iterators.  This is the
  // character string used to "generate" permutations.
  template<typename ForwardIteratorT>
  CharPermutationRank(ForwardIteratorT iBegin, ForwardIteratorT iEnd)
    : str(iBegin, iEnd), occurrences()
  {
    // Compute occurrence counts for each distinct char in the
    // provided char range.  Note that the functional object is a
    // lambda function introduced in C++11.
    std::for_each(str.begin(), str.end(),
                  [this](char c)
                  {
                    ++occurrences[CharIntervalType::getIndex(c)];
                  });
  }
  explicit CharPermutationRank(const char * cstr)
    : CharPermutationRank(cstr, cstr ? cstr + std::strlen(cstr) : 0)
  {}
  explicit CharPermutationRank(const std::string & str)
    : CharPermutationRank(str.begin(), str.end())
  {}

  // String used to "generate" permutations
  const std::string & getString() const
  {
    return(str);
  }

  std::size_t getStringSize() const
  {
    return(str.size());
  }

  const AllCharOccurrencesType & getAllCharOccurrences() const
  {
    return(occurrences);
  }

  // Get the occurrence count for a particular character in the
  // generator string
  static CharOccurrenceType
  getCharCount(char c, const AllCharOccurrencesType & occurrences)
  {
    return(occurrences[CharIntervalType::getIndex(c)]);
  }
  CharOccurrenceType getCharCount(char c) const
  {
    return(getCharCount(c, occurrences));
  }

  // This can side-effect an occurrence count (note that a non-const
  // reference is returned)
  static CharOccurrenceType &
  getCharCount(char c, AllCharOccurrencesType & occurrences)
  {
    return(occurrences[CharIntervalType::getIndex(c)]);
  }
  CharOccurrenceType & getCharCount(char c)
  {
    return(getCharCount(c, occurrences));
  }

  // Sum the occurrence counts of all characters that alphabetically
  // precede the provided char, e.g., for the word "apple", the char
  // count before "l" is 2.
  static CharOccurrenceType
  getCharCountBefore(char c, const AllCharOccurrencesType & occurrences)
  {
    return(std::accumulate(occurrences.begin(),
                           std::next(occurrences.begin(),
                                     CharIntervalType::getIndex(c)),
                           CharOccurrenceType(0)));
  }
  CharOccurrenceType getCharCountBefore(char c) const
  {
    return(getCharCountBefore(c, occurrences));
  }

  // Number of permutations that can be generated from originating
  // string.  Be mindful that this could overflow a 64-bit unsigned
  // int but we'll live dangerously...
  RankType getPermutationsCount() const
  {
    return(factorial(getStringSize()) /
           std::accumulate(occurrences.cbegin(), occurrences.cend(),
                           RankType(1),
                           [](RankType product, CharOccurrenceType occurrence)
                           {
                             return(occurrence < 2 ? product :
                                    product * factorial(occurrence));
                           }));
  }

  // Find the rank of a character string (provided by a pair of
  // iterators specifying a character range) in the permutations
  // "generated" from the originating char string.  The permutation
  // ordering by default is standard alphabetical order.
  template<typename ForwardIteratorT>
  RankType operator()(ForwardIteratorT iBegin, ForwardIteratorT iEnd,
                      LexicographicOrder order = StandardOrder) const
  {
    switch(order)
    {
    case StandardOrder: return(getStandardOrderRank(iBegin, iEnd));
    case ReverseOrder : return(getReverseOrderRank(iBegin, iEnd));
    default: assert(0 && "Unhandled enum constant");
    }
  }
  // Find the rank of the originating char string
  RankType operator()(LexicographicOrder order = StandardOrder) const
  {
    return((*this)(str.begin(), str.end(), order));
  }
  // Find the rank of the provided C char string
  RankType operator()(const char * cstr,
                      LexicographicOrder order = StandardOrder) const
  {
    return((*this)(cstr, (cstr ? cstr + std::strlen(cstr) : 0), order));
  }
  // Find the rank of the provided char string
  RankType operator()(const std::string & s,
                      LexicographicOrder order = StandardOrder) const
  {
    return((*this)(s.begin(), s.end(), order));
  }
private:
  // This does all of the "heavy lifting" to find the rank of the
  // provided char string using standard alphabetical ordering
  template<typename ForwardIteratorT>
  RankType
  getStandardOrderRank(ForwardIteratorT iBegin, ForwardIteratorT iEnd) const
  {
    using DistanceType =
      typename std::iterator_traits<ForwardIteratorT>::difference_type;
    // Length of character string passed in
    const DistanceType sizeToRank(std::distance(iBegin, iEnd));

    // Is the string to rank empty?
    if (sizeToRank == 0)
      return(1);

    const std::size_t sizeToPermute(getStringSize());

    // Is the string used to logically generate permutations empty?
    if (sizeToPermute == 0)
      return(1);

    // We will iterate through each prefix string of the passed in
    // string up to and including the length of the generating string
    // that gives rise to the permutations.  For example, if the
    // passed in string is "abcd" and the generating string has three
    // characters then there are three prefix strings we will go
    // through: "a", "ab", "abc".

    // Iterator used to refer to the last character of each prefix
    // string of the passed in character string
    ForwardIteratorT iUltimate(iBegin);
    // Iterator used to refer to the next-to-last character of each
    // prefix string of the passed in character string (for prefix
    // strings of length at least two).
    ForwardIteratorT iPenultimate(iBegin);
    const ForwardIteratorT iEndToRank(sizeToRank <= sizeToPermute ? iEnd :
                                      std::next(iBegin, sizeToPermute));

    AllCharOccurrencesType occurrencesToRank(occurrences);

    RankType rank(0);
    std::size_t permutationLengthCounter(1);

    for(RankType countToPenultimate(1);
        iUltimate != iEndToRank;
        ++iUltimate, ++permutationLengthCounter)
    {
      if (permutationLengthCounter > 1)
      {
        if (permutationLengthCounter > 2)
          ++iPenultimate;
        countToPenultimate *= getCharCount(*iPenultimate, occurrencesToRank);
        --getCharCount(*iPenultimate, occurrencesToRank);
      }
      // Each iteration we are counting permutations that come before,
      // where "before" means with respect to the prefix string up to
      // the current penultimate character and all characters
      // alphabetically before the current ultimate char.
      rank += (countToPenultimate *
               getCharCountBefore(*iUltimate, occurrencesToRank) *
               factorial(sizeToPermute - permutationLengthCounter)) /
              (std::accumulate(occurrences.cbegin(), occurrences.cend(),
                               RankType(1),
                               [](RankType product,
                                  CharOccurrenceType occurrence)
                               {
                                 return(occurrence < 2 ? product :
                                        product * factorial(occurrence));
                               }));
    }
    return(rank + 1);
  }

  // Handle rank in a reverse alphabetical order context by using the
  // standard order rank

  template<typename ForwardIteratorT>
  RankType
  getReverseOrderRank(ForwardIteratorT iBegin, ForwardIteratorT iEnd) const
  {
    const RankType standardOrderRank(getStandardOrderRank(iBegin, iEnd));
    const RankType totalCount(getPermutationsCount());
    if (standardOrderRank > totalCount)
      return(1);
    else
    {
      AllCharOccurrencesType rangeOccurrences{{}};
      std::for_each(iBegin, iEnd,
                    [&rangeOccurrences](char c)
                    {
                      ++rangeOccurrences[CharIntervalType::getIndex(c)];
                    });
      // Is the argument character string equal to a permutation?
      if (rangeOccurrences == occurrences) // yes, it is
        return(totalCount - standardOrderRank + 1);
      else return(totalCount - standardOrderRank + 2); // no, it's not
    }
  }

  // Representation
  std::string str;
  AllCharOccurrencesType occurrences;
};

int main(int argc, char * argv[])
{
  // Wrong number of arguments?
  if (argc != 2)
  {
    std::cerr << "Call: ";
    std::for_each(argv, argv + argc,
                  [](const char * arg)
                  {
                    std::cerr << arg << ' ';
                  });
    std::cerr << std::endl
              << "Usage: " << argv[0] << " <word for permutations>"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // What character interval?

  std::cout << "What character interval?"
               " [1 = Uppercase, 2 = Lowercase, 3 = Digits] ";
  std::string charIntervalChoiceStr;
  std::getline(std::cin, charIntervalChoiceStr);
  std::istringstream iss(charIntervalChoiceStr);
  int charIntervalChoice = 0;
  iss >> charIntervalChoice;
  if (!iss || charIntervalChoice < 1 || charIntervalChoice > 3)
  {
    std::cerr << "\nInvalid character interval choice." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // What string to rank?

  std::cout << "\nWhat string to rank? (Hit Enter key for \""
            << argv[1] << "\") ";
  std::string stringChoice;
  std::getline(std::cin, stringChoice);
  if (stringChoice.empty())
    stringChoice = argv[1];

  // What order to rank?

  std::cout << "\nWhat order to rank?"
               " [1 = Alphabetical order, 2 = Reverse alphabetical order] ";
  std::string orderChoiceStr;
  std::getline(std::cin, orderChoiceStr);
  iss.clear();
  iss.str(orderChoiceStr);
  iss.seekg(0);
  int orderChoice = 0;
  iss >> orderChoice;
  if (!iss || orderChoice < 1 || orderChoice > 2)
  {
    std::cerr << "\nInvalid order to rank string." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // Check that each character of the string (both the string to
  // generate permutations and the string to find the rank of, they
  // can be different) is either a member of the selected char
  // interval or can be converted to a character of this char
  // interval.

  // Check string used to generate permutations
  std::for_each(argv[1], argv[1] + std::strlen(argv[1]),
                [charIntervalChoice](char & arg)
                {
                  switch(charIntervalChoice)
                  {
                  case 1:
                    arg = UppercaseInterval::toValid(arg);
                    break;
                  case 2:
                    arg = LowercaseInterval::toValid(arg);
                    break;
                  case 3:
                    arg = DigitInterval::toValid(arg);
                    break;
                  default:
                    std::cerr << "\nUnknown character interval." << std::endl;
                    std::exit(EXIT_FAILURE);
                  }
                });

  // Check string used to find rank
  std::for_each(stringChoice.begin(), stringChoice.end(),
                [charIntervalChoice](char & arg)
                {
                  switch(charIntervalChoice)
                  {
                  case 1:
                    arg = UppercaseInterval::toValid(arg);
                    break;
                  case 2:
                    arg = LowercaseInterval::toValid(arg);
                    break;
                  case 3:
                    arg = DigitInterval::toValid(arg);
                    break;
                  default:
                    std::cerr << "\nUnknown character interval." << std::endl;
                    std::exit(EXIT_FAILURE);
                  }
                });

  switch(charIntervalChoice)
  {
  case 1:
    {
      CharPermutationRank<UppercaseInterval> r1(argv[1]);
      switch(orderChoice)
      {
      case 1:
        std::cout << '\n' << stringChoice << " = "
                  << r1(stringChoice,
                        CharPermutationRank<UppercaseInterval>::StandardOrder)
                  << std::endl;
        break;
      case 2:
        std::cout << '\n' << stringChoice << " = "
                  << r1(stringChoice,
                        CharPermutationRank<UppercaseInterval>::ReverseOrder)
                  << std::endl;
        break;
      default:
        std::cerr << "\nUnknown rank order." << std::endl;
        std::exit(EXIT_FAILURE);
      }
      break;
    }
  case 2:
    {
      CharPermutationRank<LowercaseInterval> r2(argv[1]);
      switch(orderChoice)
      {
      case 1:
        std::cout << '\n' << stringChoice << " = "
                  << r2(stringChoice,
                        CharPermutationRank<LowercaseInterval>::StandardOrder)
                  << std::endl;
        break;
      case 2:
        std::cout << '\n' << stringChoice << " = "
                  << r2(stringChoice,
                        CharPermutationRank<LowercaseInterval>::ReverseOrder)
                  << std::endl;
        break;
      default:
        std::cerr << "\nUnknown rank order." << std::endl;
        std::exit(EXIT_FAILURE);
      }
      break;
    }
  case 3:
    {
      CharPermutationRank<DigitInterval> r3(argv[1]);
      switch(orderChoice)
      {
      case 1:
        std::cout << '\n' << stringChoice << " = "
                  << r3(stringChoice,
                        CharPermutationRank<DigitInterval>::StandardOrder)
                  << std::endl;
        break;
      case 2:
        std::cout << '\n' << stringChoice << " = "
                  << r3(stringChoice,
                        CharPermutationRank<DigitInterval>::ReverseOrder)
                  << std::endl;
        break;
      default:
        std::cerr << "\nUnknown rank order." << std::endl;
        std::exit(EXIT_FAILURE);
      }
      break;
    }
  default:
    std::cerr << "\nUnknown character interval." << std::endl;
    std::exit(EXIT_FAILURE);
  }
}
