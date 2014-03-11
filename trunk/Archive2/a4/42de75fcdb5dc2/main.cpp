# Bao gồm <vector> 
# include
 
cấu trúc B { } ; 
cấu trúc D : B { } ;
 
enum  lớp E { ONE, HAI, BA } ; 
enum EU { ONE, HAI, BA } ;
 
int chính ( ) 
{ 
    / / 1: khởi tạo chuyển đổi 
    int n =  static_cast < int > ( 3.14 ) ;  
    std :: cout  <<  "n ="  << n <<  ' \ n ' ; 
    std :: vector < int > v =  static_cast < std :: vector < int >> ( 10 ) ; 
    std :: cout  <<  "v.size () ="  << v kích thước ( )  <<  ' \ n ' ;
 
    / / 2: tĩnh nhìn xuống 
    D d ; 
    B & br = d ;  / / ném lên thông qua chuyển đổi ngầm 
    D & another_d =  static_cast < D & > ( br ) ;  / / buồn mỏi mệt
 
    / / 3: giá trị trái để xvalue 
    std :: vector < int > v2 =  static_cast < std :: vector < int > && > ( v ) ; 
    std :: cout  <<  "sau khi di chuyển, v.size () ="  << v Kích thước ( )  <<  ' \ n ' ;
 
    / / 4: loại bỏ giá trị biểu 
    static_cast < trống > ( . v2 kích thước ( ) ) ;
 
    / / 5. nghịch đảo của ngầm chuyển đổi 
    / / todo
 
    / / 6. mảng đến con trỏ tiếp theo ném lên 
    D một [ 10 ] ; 
    B * dp =  static_cast < B * > ( một ) ;
 
    / / 7. scoped enum để int hoặc float 
    E e = E :: ONE ; 
    int một =  static_cast < int > ( e ) ;
 
    / / 8. int để enum, enum khác enum 
    E e2 =  static_cast < E > ( một ) ; 
    EU eu =  static_cast < EU > ( e2 ) ;
 
    / / 9. con trỏ đến thành viên ném lên 
    / / todo
 
    / / 10. void * cho bất kỳ loại 
    trống * voidp =  & điện tử ; 
    std :: vector < int > * p =  static_cast < std :: vector < int > * > ( voidp ) ; 
}