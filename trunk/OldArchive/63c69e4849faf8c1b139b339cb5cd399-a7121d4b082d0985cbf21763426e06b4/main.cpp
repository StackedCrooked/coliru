{-# LANGUAGE FlexibleInstances #-}

import Control.Applicative

class Something s

class MyClass m where
  myPure :: Something s => a -> m s a
  myAp :: Something s => m s (a -> b) -> m s a -> m s b

instance (Something s, MyClass m) => Applicative (m s) where
  pure = myPure
  (<*>) = myAp
instance (Something s, MyClass m) => Functor (m s) where
  fmap f x = pure f <*> x

foo f x = f <*> x

newtype T s a = T { runT :: s -> (s, a) }

instance MyClass T where
  myPure x = T $ \s -> (s, x)
  myAp (T tf) (T tx) = T $ \s -> let (s', f) = tf s
                                     (s'', x) = tx s'
                                 in (s'', f x)

bar :: (Something s, MyClass m) => m s a -> a -> m s a
bar p x = p *> pure x
