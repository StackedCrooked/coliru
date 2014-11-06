#include <iostream>
#include <string.h> // memcpy
#include <stdlib.h> //realloc

////////////////////////////////////////////////////////////////////////////////////////////////////
// パラメータ設定
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 手番
static const int TURN = 5 ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 移動方向の数
static const int MOVENUM = 8 ;  

////////////////////////////////////////////////////////////////////////////////////////////////////
// 開始地点と目的地の定義用クラス
template <int X, int Y>
class Position
{
public:
  static const int x = X ;
  static const int y = Y ;
} ;

typedef Position<3,3> Start ;
typedef Position<3,5> Goal ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 数学関数
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// べき乗計算クラス
template <int Base, int Exponent>
class Power
{
public:
  static const int value = Base * Power<Base, Exponent-1>::value ;
} ;

template <int Base>
class Power<Base, 0>
{
public:
  static const int value = 1 ;
} ;  

////////////////////////////////////////////////////////////////////////////////////////////////////
// 経路データ構造
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 経路データ用クラス
template <int Times, unsigned int N>
class Route
{
public:
  static const int          times = Times ;
  static const unsigned int route = N ; // 今回の問題では4回の移動分の文字列保存すればよいので，4byteのunsigned intとした

  static void Write()
  {
    unsigned int tempValue = route ;
    char str[5] ;
    memcpy( str, ( char*)&tempValue, 4 ) ;
    str[4] = '\0' ;
    Padding( str, TURN - times ) ;
  }

private:
  static void Padding( std::string str, int chNum )
  {
    if ( chNum == 0 ) {
      std::cout << str.c_str() << std::endl ;
      return ;
    }

    for ( char ch = 'A' ; ch < 'I' ; ++ch ) {
      char temp[2] = { ch, 0 } ;
      std::string tempStr = str ;
      tempStr += std::string( temp ) ;
      Padding( tempStr, chNum - 1 ) ; 
    }
  }
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 経路データリストの末尾を表すダミークラス
class EndSentinel
{
public:
  static const unsigned int value = 0 ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 経路データリストの各ノード
template <typename H, typename T>
class RouteNode
{
public:  
  typedef H head ;
  typedef T tail ;

  typedef RouteNode<H,T> node ;

  static void Write()
  {
    head::Write() ;
    tail::Write() ;
  }
} ;

//////////////////////////////////////////////////
// 経路データリストの縮約のための特殊化
template <typename H>
class RouteNode<H, EndSentinel>
{
public:
  typedef H           head ;
  typedef EndSentinel tail ;

  typedef H           node ;
} ;

//////////////////////////////////////////////////
// 経路データリストの縮約のための特殊化
template <typename T>
class RouteNode<EndSentinel, T>
{
public:
  typedef EndSentinel head ;
  typedef T           tail ;

  typedef T           node ;
} ;

//////////////////////////////////////////////////
// 経路データリストの縮約のための特殊化
template <>
class RouteNode<EndSentinel, EndSentinel>
{
public:
  typedef EndSentinel head ;
  typedef EndSentinel tail ;

  typedef EndSentinel node ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 経路の延長を行うクラス
template <int Times, unsigned int ID, typename T>
class Move ;

//////////////////////////////////////////////////
// 経路データに対しての延長
template <int Times, unsigned int ID, int T, unsigned int N>
class Move<Times, ID, Route<T,N>>
{
public:
  typedef Route<Times,((Route<T,N>::route << 8)|ID)> moved ;
} ;

//////////////////////////////////////////////////
// ダミーは延長してもダミーのまま
template <int Times, unsigned int ID>
class Move<Times, ID, EndSentinel>
{
public:
  typedef EndSentinel moved ;
} ;

//////////////////////////////////////////////////
// リストの全てのノードに対して延長を行う
template <int Times, unsigned int ID, typename H, typename T>
class Move<Times, ID, RouteNode<H, T>>
{
private:
  typedef typename RouteNode<H,T>::head nodeHead ;
  typedef typename RouteNode<H,T>::tail nodeTail ;
  typedef typename Move<Times,ID,nodeHead>::moved movedHead ;
  typedef typename Move<Times,ID,nodeTail>::moved movedTail ;

public:
  typedef typename RouteNode<movedHead,movedTail>::node moved ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// マス目毎の計算用
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <int Times, int X, int Y>
class Square ;

////////////////////////////////////////////////////////////////////////////////////////////////////
template <bool bStart, bool bOriginX, bool bOriginY, int Times, int X, int Y>
class dispatcher
{
public:
  // (X,Y)マスに移動してくるパターン数
  static const int value = Square<Times-1, X+1, Y-2>::patternNum
                         + Square<Times-1, X-1, Y-2>::patternNum
                         + Square<Times-1, X+2, Y-1>::patternNum
                         + Square<Times-1, X-2, Y-1>::patternNum
                         + Square<Times-1, X+2, Y+1>::patternNum
                         + Square<Times-1, X-2, Y+1>::patternNum
                         + Square<Times-1, X+1, Y+2>::patternNum
                         + Square<Times-1, X-1, Y+2>::patternNum ;

private:
  // (X,Y)マスに移動してくる前のマスの経路データを取得
  typedef typename Square<Times-1, X+1, Y-2>::route movedByA ;
  typedef typename Square<Times-1, X-1, Y-2>::route movedByB ;
  typedef typename Square<Times-1, X+2, Y-1>::route movedByC ;
  typedef typename Square<Times-1, X-2, Y-1>::route movedByD ;
  typedef typename Square<Times-1, X+2, Y+1>::route movedByE ;
  typedef typename Square<Times-1, X-2, Y+1>::route movedByF ;
  typedef typename Square<Times-1, X+1, Y+2>::route movedByG ;
  typedef typename Square<Times-1, X-1, Y+2>::route movedByH ;

  // 各routeに最近の移動分の経路データを追加
  typedef typename Move<Times, static_cast<unsigned int>('A'), movedByA>::moved routeA ;
  typedef typename Move<Times, static_cast<unsigned int>('B'), movedByB>::moved routeB ;
  typedef typename Move<Times, static_cast<unsigned int>('C'), movedByC>::moved routeC ;
  typedef typename Move<Times, static_cast<unsigned int>('D'), movedByD>::moved routeD ;
  typedef typename Move<Times, static_cast<unsigned int>('E'), movedByE>::moved routeE ;
  typedef typename Move<Times, static_cast<unsigned int>('F'), movedByF>::moved routeF ;
  typedef typename Move<Times, static_cast<unsigned int>('G'), movedByG>::moved routeG ;
  typedef typename Move<Times, static_cast<unsigned int>('H'), movedByH>::moved routeH ;

  // 経路データリストへ詰め込む
  typedef typename RouteNode<routeH, EndSentinel>::node NodeH ;
  typedef typename RouteNode<routeG, NodeH>::node       NodeG ;
  typedef typename RouteNode<routeF, NodeG>::node       NodeF ;
  typedef typename RouteNode<routeE, NodeF>::node       NodeE ;
  typedef typename RouteNode<routeD, NodeE>::node       NodeD ;
  typedef typename RouteNode<routeC, NodeD>::node       NodeC ;
  typedef typename RouteNode<routeB, NodeC>::node       NodeB ;
  typedef typename RouteNode<routeA, NodeB>::node       NodeA ;

public:
  typedef NodeA moved ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 0回目，スタート地点以外のデータ
template <bool bOriginX, bool bOriginY, int Times, int X, int Y>
class dispatcher<true, bOriginX, bOriginY, Times, X, Y>
{
public:
  static const int value = 0 ;
  typedef EndSentinel moved ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 0回目，スタート地点のデータ
template <int Times, int X, int Y>
class dispatcher<true, true, true, Times, X, Y>
{
public:
  static const int value = 1 ;
  typedef Route<0,0> moved ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 0回目以外，スタート地点のデータ
template <int Times, int X, int Y>
class dispatcher<false, true, true, Times, X, Y>
{
public:
  static const int value = 0 ;
  typedef EndSentinel moved ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
// (X,Y)マスにちょうどTimes回で到着するパターン数と経路データリストを保持するクラス
template <int Times, int X, int Y>
class Square
{
public:
  static const int patternNum = dispatcher<(Times==0),(X==Start::x),(Y==Start::y),Times,X,Y>::value ;

  typedef typename dispatcher<(Times==0),(X==Start::x),(Y==Start::y),Times,X,Y>::moved route ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  Square<4,Goal::x,Goal::y>::route::Write() ;
  Square<2,Goal::x,Goal::y>::route::Write() ;

  std::cout << "Pattern Num : "   
            << Square<4,Goal::x,Goal::y>::patternNum*Power<MOVENUM,TURN-4>::value
             + Square<2,Goal::x,Goal::y>::patternNum*Power<MOVENUM,TURN-2>::value
            << std::endl ;  
}