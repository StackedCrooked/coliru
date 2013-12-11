#include <memory>
#include <vector>
#include <cassert>

template<class T>
class RedBlackTree
{
   enum Color { Red, Black, DoubleBlack };

   struct Node
   {
      Node( Color c
          , std::shared_ptr<Node const> const & lft
          , T val
          , std::shared_ptr<Node const> const & rgt)
      : _color( c )
      , _lft( lft )
      , _val( val )
      , _rgt( rgt )
      {
      }

      Color _color;
      std::shared_ptr<Node const> _lft;
      T _val;
      std::shared_ptr<Node const> _rgt;
   };

   struct ColorTree
   {
   public:

      Color const color;
      RedBlackTree const tree;
   
      static ColorTree doubleBlack()
      {
         return ColorTree();
      }

      explicit
      ColorTree( RedBlackTree const & tree )
      : color( tree.rootColor() )
      , tree( tree )
      {
      }

      explicit
      ColorTree( Color c
               , RedBlackTree const & lft
               , T x
               , RedBlackTree const & rgt )
      : color( c )
      , tree( c, lft, x, rgt )
      {
      }



   private:


      ColorTree( )
      : color( DoubleBlack )
      {
      }

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
      return RedBlackTree( _root->_lft );
   }

   RedBlackTree right() const 
   {
      assert(!isEmpty());
      return RedBlackTree( _root->_rgt );
   }

   Color rootColor() const
   {
      assert( !isEmpty() );
      return _root->_color;
   }

   RedBlackTree insert(T x) const 
   {
      RedBlackTree t = ins(x);
      return RedBlackTree( Black, t.left(), t.root(), t.right() );
   }

   RedBlackTree remove(T x) const
   {
      auto t = rem( x ).tree;

      if( t.isEmpty() )
         return RedBlackTree();
      else
         return RedBlackTree(Black, t.left(), t.root(), t.right());
   }

private:

   RedBlackTree( Color c,
                 RedBlackTree const & lft,
                 T val,
                 RedBlackTree const & rgt)
   : _root( std::make_shared<Node>( c, lft._root, val, rgt._root ) )
   {
   }

   RedBlackTree( std::shared_ptr<const Node> const & node )
   : _root( node )
   {
   }

   
   ColorTree rem(T x) const
   {
      if (isEmpty())
         return ColorTree( RedBlackTree() );
      T y = root();
      if(x < y)
         return removeDoubleBlack( rootColor(), left().rem( x ), y, ColorTree( right() ) );
      else if(y < x)
         return removeDoubleBlack( rootColor(), ColorTree( left() ), y, right().rem( x ) );
      else
      {
         return remove();
      }
   }

   ColorTree remove() const
   {
      if( ! left().isEmpty() && ! right().isEmpty() )
      {
         RedBlackTree p = pred();
         T x = p.root();

         Color c = rootColor();

         return removeDoubleBlack( c, left( ).rem( x ), x, ColorTree( right( ) ) );
      }
      else if( ! left().isEmpty() )
      {
         return ColorTree( left().paint( Black ) );
      }
      else if( ! right().isEmpty() )
      {
         return ColorTree( right( ).paint( Black ) );
      }
      else if( rootColor() == Black )
      {
         return ColorTree::doubleBlack();
      }
      else
      {
         return ColorTree( RedBlackTree() );
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
   ColorTree
   removeDoubleBlack( Color c
                    , ColorTree const & lft
                    , T x
                    , ColorTree const & rgt )
   {
      if( lft.color == DoubleBlack )
      {
         auto left = lft.tree.isEmpty() ? RedBlackTree() : lft.tree.paint( Black );

         if( rgt.color == Black )
         {
            assert( c != DoubleBlack );
            return ColorTree( Color( c+1 ), left, x, rgt.tree.paint( Red ) );
         }
         else
            return ColorTree( Black
                            , RedBlackTree( Black, left, x, rgt.tree.left( ).paint(Red) )
                            , rgt.tree.root()
                            , rgt.tree.right() 
                            );
      }
      else if( rgt.color == DoubleBlack )
      {
         auto right = rgt.tree.isEmpty() ? RedBlackTree() : rgt.tree.paint( Black );

         if( lft.color == Black )
         {
            assert( c != DoubleBlack );
            return ColorTree( Color( c+1 ), lft.tree.paint( Red ), x, right );
         }
         else
            return ColorTree( Black
                            , lft.tree.left()
                            , lft.tree.root()
                            , RedBlackTree( Black, lft.tree.right( ).paint(Red), x, right )
                            );
      }
      else
         return ColorTree( c, lft.tree, x, rgt.tree );
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
      assert( ! isEmpty() );
      return RedBlackTree( c, left(), root(), right() );
   }

   //Color _rootColor;
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

   auto i = f.remove( 6 );
   auto j = f.remove( 2 );
   auto k = f.remove( 1 );
}
