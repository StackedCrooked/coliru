#include <fcntl.h>
#include <io.h>
#include <stdio.h>
 
#include <windows.h>
 
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
 
namespace
{
  const int g_triplet_size = 3;
}
/////////////////////////////////////////////////////////////////////////////////////////
typedef std::wstring    T_wstr;
/////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::wstring> break_word_to_triplets( const std::wstring& a_str ) 
{
  if( a_str.size() < g_triplet_size )
  {
    return std::vector<std::wstring>();
  }

  std::vector<std::wstring> triplets;
  for( std::size_t i = 0; i <= a_str.size() - g_triplet_size; ++i )
  {
    triplets.push_back( a_str.substr( i, g_triplet_size ) );
  }
 
  return triplets;
}
/////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::wstring> break_sentence_to_triplets( std::wstring a_str )
{
  std::transform( a_str.cbegin(), a_str.cend(), a_str.begin(), &tolower );
  std::vector < std::wstring > triplets;
 
  std::wistringstream ss( a_str );
  std::wstring str;
  while( ss >> str ) 
  {
    auto word_triplets = break_word_to_triplets( str );
    triplets.insert
        (
            triplets.end(),
            std::make_move_iterator( word_triplets.begin() ),
            std::make_move_iterator( word_triplets.end() ) );
        }
 
  return triplets;
}
/////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  _setmode( _fileno( stdout ), _O_U8TEXT );
  ::SetConsoleOutputCP( CP_UTF8 );
 
  std::wstring input = L"Карл у Клары украл кораллы, а Клара у Карла украла кларнет";
  auto triplets = break_sentence_to_triplets( input );
  typedef std::map<const std::wstring, int> TripletMap;
  TripletMap map;
  for( const auto& triplet : triplets )
  {
    map[ triplet ] += 1;
  }
 
  auto iter     =   std::max_element
                        (
                            map.cbegin(),
                            map.cend(),
                            std::bind
                                (
                                    std::less<int>(),
                                    std::bind
                                        (
                                            &TripletMap::value_type::second,
                                            std::placeholders::_1
                                        ),
                                    std::bind
                                        (
                                            &TripletMap::value_type::second,
                                            std::placeholders::_2
                                        )
                                 )
                         );

  std::wcout << iter->first << L" : " << iter->second << L"\n";
}