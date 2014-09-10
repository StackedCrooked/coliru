{-# LANGUAGE PolyKinds, DataKinds, GADTs, KindSignatures, StandaloneDeriving #-}

data Nat = Z | S Nat deriving Show
data SNat :: Nat -> * where
  SZ :: SNat Z
  SS :: SNat n -> SNat (S n)
  
infixr 5 `Cons`
data Vec :: Nat -> * -> * where
  Nil :: Vec Z a
  Cons :: a -> Vec n a -> Vec (S n) a

deriving instance (Show a) => Show (Vec n a)
  
make :: SNat n -> a -> Vec n a
make SZ _ = Nil
make (SS n) a = a `Cons` make n a

main = print $ make (SS $ SS $ SS SZ) 42