{-# LANGUAGE FlexibleInstances #-}

module Main where

f a b = a + b
g a = a * 2

class CH a where
  (<.<) :: (b -> c) -> a -> (i -> c)

instance (CH c) => CH (a -> b -> c) where
  g <.< f = \a -> g <.< f a

instance CH (a -> b) where
  g <.< f = g . f

main = print $ (g <.< f) 2 3