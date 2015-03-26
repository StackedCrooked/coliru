#include <functional>

struct C
{
    int x ;
    std::function< int (void) > f()
    {
        return [=]{ return x ; } ;
    }
} ;

int main()
{
    std::function< int (void) > f ;
    {
        C c ;
        f = c.f() ;
    }// cの寿命終了のお知らせ

    f() ;// 実行時エラー、オブジェクトはすでに死んでいる
}