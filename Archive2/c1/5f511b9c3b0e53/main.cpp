{-# LANGUAGE RankNTypes, NoMonomorphismRestriction #-}

import Control.Applicative
import Control.Monad.IO.Class

-- Not your usual continuation
-- Also see package managed for an IO-specific version
newtype Cont f a = Cont { runCont :: forall r. (a -> f r) -> f r }
run :: (Monad f) => Cont f () -> f ()
run c = runCont c return

instance Functor (Cont f) where
    fmap f (Cont c) = Cont $ \k -> c (k . f)

instance Applicative (Cont f) where
    pure a = Cont $ \k -> k a
    Cont cf <*> Cont ca = Cont $ \k -> cf (\f -> ca (\a -> k (f a)))

instance Monad (Cont f) where
    return = pure
    Cont ca >>= f = Cont $ \k -> ca (\a -> runCont (f a) $ \b -> k b)
    
instance MonadIO f => MonadIO (Cont f) where
    liftIO fa = Cont $ \k -> do { a <- liftIO fa; k a }
    
putStrLnIO = liftIO . putStrLn
    
bells = Cont $ \k -> do
    putStrLnIO $ "Putting the bells on!"
    a <- k ()
    putStrLnIO $ "Putting down the bells."
    return a

-- seeing a pattern here
bracket_ before after = Cont $ \k -> do
    before
    a <- k ()
    after
    return a

whistles = bracket_ (putStrLnIO "Putting the whistles on!") (putStrLnIO "Putting the whistles down.")
    
main = run $ do
    bells
    whistles
    putStrLnIO "Pull the other one."