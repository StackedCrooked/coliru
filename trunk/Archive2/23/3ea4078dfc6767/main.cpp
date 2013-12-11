#include <memory>
#include <vector>
#include <cassert>

template<class T>
class RedBlackTree
{
   enum Color { Red, Black, DoubleBlack };

   struct Node
   {
      Node( std::shared_ptr<Node const> const & lft,
            T val,
            std::shared_ptr<Node const> const & rgt)
      : _lft(lft)
      , _val(val)
      , _rgt(rgt)
      {
      }

      std::shared_ptr<Node const> _lft;
      T _val;
      std::shared_ptr<Node const> _rgt;
   };

public:

   RedBlackTree()
   {
   }

   bool isEmpty() const
   {
      return !_root;
   }

   bool member(T x) const
   {
      if (isEmpty())
         return false;
      T y = root();
      if (x < y)
         return left().member(x);
      else if (y < x)
         return right().member(x);
      else
         return true;
   }

   T root() const {
      assert(!isEmpty());
      return _root->_val;
   }

   RedBlackTree left() const 
   {
      assert(!isEmpty());
      return RedBlackTree( _rootColor, _root->_lft );
   }

   RedBlackTree right() const 
   {
      assert(!isEmpty());
      return RedBlackTree( _rootColor, _root->_rgt );
   }

   Color rootColor() const
   {
      return _rootColor;
   }

   RedBlackTree insert(T x) const 
   {
      RedBlackTree t = ins(x);
      return RedBlackTree( Black, t.left(), t.root(), t.right() );
   }

   RedBlackTree remove(T x) const
   {
      RedBlackTree t = rem( x );
      return RedBlackTree(Black, t.left(), t.root(), t.right());
   }

private:

   RedBlackTree( Color c,
                 RedBlackTree const & lft,
                 T val,
                 RedBlackTree const & rgt)
   : _rootColor( c )
   , _root( std::make_shared<Node>( lft._root, val, rgt._root ) )

   {
   }

   RedBlackTree( Color c, std::shared_ptr<const Node> const & node )
   : _rootColor( c )
   , _root( node )
   {
   }

   
   RedBlackTree rem(T x) const
   {
      if (isEmpty())
         return RedBlackTree();
      T y = root();
      if(x < y)
         return removeDoubleBlack( rootColor(), left().rem( x ), y, right() );
      else if(y < x)
         return removeDoubleBlack( rootColor(), left(), y, right().rem( x ) );
      else
      {
         return remove();
      }
   }

   RedBlackTree remove() const
   {
      if( ! left().isEmpty() && ! right().isEmpty() )
      {
         RedBlackTree p = pred();
         T x = p.root();

         return removeDoubleBlack( rootColor(), left( ).rem( x ), x, right( ) );
      }
      else if( ! left().isEmpty() )
      {
         return left().paint( Black );
      }
      else if( ! right().isEmpty() )
      {
         return right( ).paint( Black );
      }
      else if( rootColor() == Black )
      {
         return RedBlackTree( DoubleBlack, nullptr );
      }
      else
      {
         return RedBlackTree();
      }
   }

   RedBlackTree pred() const
   {
      RedBlackTree t = left();
      while (!t.right().isEmpty())
         t = t.right();

      return t;
   }

   RedBlackTree ins(T x) const
   {
      if (isEmpty())
         return RedBlackTree( Red, RedBlackTree(), x, RedBlackTree() );
      T y = root();
      if (x < y)
         return balance( rootColor(), left().ins(x), y, right() );
      else if (y < x)
         return balance( rootColor(), left(), y, right().ins(x) );
      else
         return *this; // no duplicates
   }

   static 
   RedBlackTree
   removeDoubleBlack( Color c
                    , RedBlackTree const & lft
                    , T x
                    , RedBlackTree const & rgt )
   {
      assert( c != DoubleBlack );

      if( lft.rootColor() == DoubleBlack )
      {
         if( rgt.rootColor( ) == Black )
         {
            return RedBlackTree( Color( c+1 ), lft.paint( Black ), x, rgt.paint( Red ) );
         }
         else
            return RedBlackTree( Black
                               , RedBlackTree( Black, lft.paint( Black ), x, rgt.left( ) )
                               , rgt.root()
                               , rgt.right() 
                               );
      }
      else if( rgt.rootColor( ) == DoubleBlack )
      {
         if( lft.rootColor( ) == Black )
            return RedBlackTree( Color( c+1 ), lft.paint( Red ), x, rgt.paint( Black ) );
         else
            return RedBlackTree( Black
                            , lft.left()
                            , lft.root()
                            , RedBlackTree( Black, lft.right( ), x, rgt.paint( Black ) )
                            );
      }
      else
         return RedBlackTree( c, lft, x, rgt );
   }


   static 
   RedBlackTree 
   balance( Color c
          , RedBlackTree const & lft
          , T x
          , RedBlackTree const & rgt)
   {
      if (c == Black && lft.doubledLeft() )
         return RedBlackTree( Red
                            , lft.left().paint(Black)
                            , lft.root()
                            , RedBlackTree(Black, lft.right(), x, rgt) 
                            );
      else if (c == Black && lft.doubledRight() )
         return RedBlackTree( Red
                            , RedBlackTree(Black, lft.left(), lft.root(), lft.right().left())
                            , lft.right().root()
                            , RedBlackTree(Black, lft.right().right(), x, rgt)
                            );
      else if (c == Black && rgt.doubledLeft() )
         return RedBlackTree( Red
                            , RedBlackTree(Black, lft, x, rgt.left().left())
                            , rgt.left().root()
                            , RedBlackTree(Black, rgt.left().right(), rgt.root(), rgt.right())
                            );
      else if (c == Black && rgt.doubledRight() )
         return RedBlackTree( Red
                            , RedBlackTree(Black, lft, x, rgt.left())
                            , rgt.root()
                            , rgt.right().paint(Black) 
                            );
      else
         return RedBlackTree(c, lft, x, rgt);
   }


   bool doubledLeft() const 
   {
      return !isEmpty()
             && rootColor() == Red
             && !left().isEmpty()
             && left().rootColor() == Red;
   }

   bool doubledRight() const 
   {
      return !isEmpty()
             && rootColor() == Red
             && !right().isEmpty()
             && right().rootColor() == Red;
   }

   RedBlackTree paint(Color c) const 
   {
      if( isEmpty() )
      {
         assert( c == DoubleBlack );
         return RedBlackTree( c, nullptr );
      }
      else
        return RedBlackTree( c, left(), root(), right() );
   }

   Color _rootColor;
   std::shared_ptr<const Node> _root;

};


int main()
{
   auto a = RedBlackTree<int>();

   auto b = a.insert(3);
   auto c = b.insert(5);
   auto d = c.insert(2);
   auto e = d.insert(1);
   auto f = e.insert(6);

   auto g = f.remove(5);
   auto h = g.remove(3);

   assert( ! g.member(5) );
   assert( ! h.member(3) );

   assert( f.member(5) );
   assert( f.member(3) );
}
