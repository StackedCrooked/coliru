{-# LANGUAGE FlexibleInstances #-}

instance Num a => Num (a, a) where
    (a1, a2) + (b1, b2) = (a1 + b1, a2 + b2)
    (a1, a2) * (b1, b2) = (a1 * b1, a2 * b2)
    abs (a, b) = (abs a, abs b)
    signum (a, b) = (signum a, signum b)
    fromInteger x = (fromInteger x, fromInteger x)
    
main :: IO ()
main = do
    print $ ((1, 3) :: (Int, Int) + ((0, 1) :: (Int, Int)