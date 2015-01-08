{-# LANGUAGE TypeSynonymInstances #-}

type Pair a = (a, a)

instance Functor Pair where
    fmap fn (x, y) = (fn x, fn y)

main :: IO ()
main = putStr "ok"