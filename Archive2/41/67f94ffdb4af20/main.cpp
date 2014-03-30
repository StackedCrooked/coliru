import Prelude hiding (null)

data Pointer a = Some a | NullPtr deriving Show -- yeah, pretty much Maybe, just roll with it

class Nullable a where
    null :: a
    
instance Nullable (Maybe a) where
    null = Nothing

instance Nullable (Pointer a) where
    null = NullPtr
    
a, b, c :: Maybe (Pointer Int)
a = null
b = Just null
c = Just $ Some 42

main = print a >> print b >> print c