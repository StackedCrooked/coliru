#include <iostream>
#include <cstdint>

struct MyStruct {
  const uint16_t index;


  MyStruct(uint16_t in) : index(in) { }
} ;

static const MyStruct array[] = {
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
 MyStruct(__COUNTER__),
} ;

int main()
{
    for( size_t i = 0; i < sizeof( array )/sizeof(MyStruct); ++i )
    {
        std::cout << i << ":" << array[i].index << ":" << std::boolalpha << ( i == array[i].index ? true : false ) << std::endl ;
    }
}
