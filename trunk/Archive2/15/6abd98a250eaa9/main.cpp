import Prelude hiding (null)

data Pointer a = Some a | NullPtr deriving Show -- yeah, pretty much Maybe, just roll with it

class Nullable a where
    null :: a
    
instance Nullable (Maybe a) where
    null = Nothing

instance Nullable (Pointer a) where
    null = NullPtr
    
instance Nullable Int where
    null = 0 -- just for fun
    
-- null :: Nullable a => a, i.e. fully polymorphic
a, b, c :: Maybe (Pointer Int)
a = null                -- 'null' specialized to 'null :: Maybe (Pointer Int)'
b = Just null           -- 'null' specialized to 'null :: Pointer Int'
c = Just $ Some null    -- 'null' specialized to 'null :: Int'

main = print a >> print b >> print c