{-# LANGUAGE TypeFamilies #-}

data Ab = A | B deriving (Show)
data Cd = C | D deriving (Show)

type family Converted a
type instance Converted Ab = Cd
type instance Converted Cd = Ab

class Convertable a where
    foo :: a -> Converted a
    
instance Convertable Ab where
    foo A = C
    foo B = D

instance Convertable Cd where
    foo C = A
    foo D = B

main :: IO ()
main = do
    print . foo $ A
    print . foo $ B
    print . foo $ C
    print . foo $ D