import Control.Applicative

newtype Vec2 a = Vec2 (a, a) deriving (Show, Eq)
newtype Vec3 a = Vec3 (a, a, a) deriving (Show, Eq)

instance Functor Vec2 where
    fmap f (Vec2 (a, b)) = Vec2 (f a, f b)
    
instance Functor Vec3 where
    fmap f (Vec3 (a, b, c)) = Vec3 (f a, f b, f c)
    
instance Applicative Vec2 where
    pure x = Vec2 (x, x)
    Vec2 (f, g) <*> Vec2 (a, b) = Vec2 (f a, g b)
    
instance Applicative Vec3 where
    pure x = Vec3 (x, x, x)
    Vec3 (f, g, h) <*> Vec3 (a, b, c) = Vec3 (f a, g b, h c)

main :: IO ()
main = do
    print $ (+) <$> Vec2 (1, 2) <*> Vec2 (2, 1)