{-# LANGUAGE TypeSynonymInstances, RankNTypes #-}

import Control.Applicative

type Vec2 = forall a. (a, a)
type Vec3 = forall a. (a, a, a)

instance Functor Vec2 where
    fmap f (a, b) = (f a, f b)
    
instance Functor Vec3 where
    fmap f (a, b, c) = (f a, f b, f c)
    
instance Applicative Vec2 where
    pure x = (x, x)
    (f, g) <*> (a, b) = (f a, g b)
    
instance Applicative Vec3 where
    pure x = (x, x, x)
    (f, g, h) <*> (a, b, c) = (f a, g b, h c)

main :: IO ()
main = do
    print $ (+) <$> (1, 2) <*> (2, 1)