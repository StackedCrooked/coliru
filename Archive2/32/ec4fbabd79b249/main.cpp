import Control.Monad.State.Class
import Control.Monad.IO.Class

class SomeClass t where
    type CacheType
    iDon'tKnow :: (MonadState CacheType m, MonadIO m) => t -> m ()
    
main :: IO ()
main = putStr "ok"