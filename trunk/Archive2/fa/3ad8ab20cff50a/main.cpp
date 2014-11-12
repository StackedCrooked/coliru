import Data.Monoid
import Data.Foldable
import Control.Applicative
import Control.Monad

data List a = List [a] deriving Show

instance Monoid (List a) where
    mempty = List $ mempty
    mappend (List l) (List r) = List $ mappend l r

instance Foldable List where
    foldMap f (List l) = foldMap f l
    
instance Monad List where
    return = List . return
    l >>= f = foldMap f l

main = do
    print $ [1,2,3] >>= (\x -> [x * 2, x * 3])
    print $ List [1,2,3] >>= (\x -> List [x * 2, x * 3])