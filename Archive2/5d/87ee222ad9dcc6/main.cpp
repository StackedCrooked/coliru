{-# LANGUAGE GeneralizedNewtypeDeriving #-}

-- Some int wrapper
newtype X = X Int deriving (Eq, Show, Num)

-- Given a function that accepts `X` ...
func :: X -> Int
func (X i) = i

-- ... we can pass any `Num` object to it.
-- Similarly to how `IsString` works with `OverloadedStrings`.
main :: IO ()
main = print $ func 5