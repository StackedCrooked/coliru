#include <cstdio> 
#include <giới hạn> 
#include <cstdint> 
#include <cinttypes>
 
int chính ( ) 
{ 
    std :: printf ( "Strings: \ n " ) ;
 
    const  char * s =  "Hello" ; 
    std :: printf ( " \ t ..% 10s \ n \ t ..% - 10s \ n \ t ..% * s \ n " , s, s, 10 , s ) ;
 
    std :: printf ( "Nhân vật: \ t % c %% \ n " , 65 ) ;
 
    std :: printf ( "số nguyên \ n " ) ; 
    std :: printf ( "thập phân: \ t % i% d% .6i% i% .0i% + i% u \ n " , 1 , 2 , 3 , 0 , 0 , 4 , - 1 ) ; 
    std :: printf ( "Hexadecimal: \ t % x% x% X% # x \ n " , 5 , 10 , 10 , 6 ) ; 
    std :: printf ( "Octal: \ t % o% #% # o o \ n " , 10 , 10 , 4 ) ;
 
    std :: printf ( "Floating điểm \ n " ) ; 
    std :: printf ( "Tròn: \ t % f% .0f% .32f \ n " , 1.5 , 1.5 , 1.3 ) ; 
    std :: printf ( "Padding: \ t % 05.2f% .2f% 5.2f \ n " , 1,5 , 1,5 , 1,5 ) ; 
    std :: printf ( "khoa học: \ t % E% e \ n " , 1.5 , 1.5 ) ; 
    std :: printf ( "Hexadecimal: \ t % a% A \ n " , 1.5 , 1.5 ) ; 
    std :: printf ( "giá trị đặc biệt: \ t 0/0 = g 1% / 0 =% g \ n " , 0 . / 0 , 1 . / 0 ) ;
 
    std :: printf ( "kiểm soát biến width: \ n " ) ; 
    std :: printf ( "phải hợp lý biến rộng: '% * c' \ n " , 5 , 'x' ) ; 
    int r = std :: printf ( "trái lý biến rộng: '% * c' \ n " , - 5 , 'x' ) ; 
    std :: printf ( "(printf in% d ký tự cuối cùng) \ n " , r ) ;
 
    // Loại cố định chiều rộng 
    std :: uint32_t val =  std :: numeric_limits < std :: uint32_t > :: max ( ) ; 
    std :: printf ( "lớn nhất giá trị 32-bit là%"  PRIu32  "hoặc% #"  PRIx32  " \ n " , val, val ) ; 
}