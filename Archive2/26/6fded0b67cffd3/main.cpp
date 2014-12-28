-- Some int wrapper
newtype X = X Int deriving (Eq, Show)

-- With some `Num` instance
instance Num X where
    (X a) + (X b) = X (a + b)
    (X a) * (X b) = X (a * b)
    abs (X a) = X (abs a)
    signum (X a) = X (signum a)
    fromInteger a = X (fromInteger a)
    negate (X a) = X (negate a)

-- Given a function that accepts `X` ...
func :: X -> Int
func (X i) = i

-- ... we can pass any `Num` object to it.
main :: IO ()
main = print $ func 5