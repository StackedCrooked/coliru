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
    
instance (Num a, Eq a) => YesNo a where
    yesNo = (== fromIntegral 0)

main :: IO ()
main = do
    print . yesNo $ Nothing
    print . yesNo $ 0
    print . yesNo $ []