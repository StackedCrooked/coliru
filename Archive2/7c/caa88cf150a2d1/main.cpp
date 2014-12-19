{-# LANGUAGE FlexibleInstances, UndecidableInstances #-}

class YesNo a where
    yesNo :: a-> Bool

instance YesNo Bool where
    yesNo True = True
    yesNo _ = False

instance YesNo [a] where
    yesNo [] = False
    yesNo _ = True

instance YesNo (Maybe a) where
    yesNo Nothing = False
    yesNo _ = True
    
instance (Num a) => YesNo a where -- error is here
    yesNo 0 = False
    yesNo _ = True

main :: IO ()
main = do
    print . yesNo $ Nothing
    print . yesNo $ 0
    print . yesNo $ []