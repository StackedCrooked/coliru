data X = X Int deriving (Eq, Show)

instance Enum X where
    toEnum = X
    fromEnum (X i) = i
    
instance Num X where
    (X a) + (X b) = X (a + b)
    (X a) * (X b) = X (a * b)
    abs (X a) = X (abs a)
    signum (X a) = X (signum a)
    fromInteger x = X (fromInteger x)
    negate (X a) = X (negate a)
    
func :: [X] -> IO ()
func = print

main :: IO ()
main = func [0..10]