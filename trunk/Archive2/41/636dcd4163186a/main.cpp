import Control.Applicative

data Vec2 a = Vec2 a a deriving (Eq, Show)

instance Functor Vec2 where
    fmap fn (Vec2 a b) = Vec2 (fn a) (fn b)

instance Applicative Vec2 where
    pure a = Vec2 a a
    (Vec2 fa fb) <*> (Vec2 a b) = Vec2 (fa a) (fb b)

instance (Num a) => Num (Vec2 a) where
    (+)           = liftA2 (+) 
    (*)           = liftA2 (*)
    abs           = fmap abs
    signum        = fmap signum
    fromInteger x = pure (fromInteger x)
    negate        = fmap negate
    
main :: IO ()
main = print $ (Vec2 2 0) * 9