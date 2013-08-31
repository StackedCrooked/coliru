{-# LANGUAGE FlexibleInstances, MultiParamTypeClasses #-}

import Control.Applicative

class Something s

class (Something s, Applicative (m s)) => MyClass m s

foo f x = f <*> x

newtype T s a = T { runT :: s -> (s, a) }

instance Something s => Applicative (T s) where
  pure x = T $ \s -> (s, x)
  (<*>) (T tf) (T tx) = T $ \s -> let (s', f) = tf s
                                      (s'', x) = tx s'
                                  in (s'', f x)
instance Something s => Functor (T s) where
  fmap f x = pure f <*> x

bar :: MyClass m s => m s a -> a -> m s a
bar p x = p *> pure x

