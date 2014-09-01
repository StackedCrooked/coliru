{-# LANGUAGE MagicHash #-}
module Main (main) where

main :: IO ()
main = print $ C# <3

data Foo = C#

instance Num Foo where
    (+) = const
    (*) = const
    (-) = const
    abs = id
    signum = id
    fromInteger = const C#

instance Eq Foo where
    (==) = const . (const True)

instance Ord Foo where
    compare = const . (const EQ)