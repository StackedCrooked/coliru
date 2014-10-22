import Control.Applicative hiding getZipList

newtype MZipList a = MZipList { getZipList :: [a] }
    deriving (Show)

instance Functor MZipList where
  fmap gs x = pure gs <*> x

instance Applicative MZipList where
  pure a= MZipList (repeat a)
  (MZipList gs) <*> (MZipList xs) = MZipList (zipWith ($) gs xs)
  
main :: IO ()
main = do
    -- taking only 10 elements because this operation is returning 
    -- a lazy infinite list
    print $ take 10 . getZipList $ pure (*2) <*> (pure 2 :: MZipList Int)