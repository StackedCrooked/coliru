import Control.Monad

data Mine a = Mine a deriving (Eq, Show)

instance Num (Mine a) where
    (Mine x) * (Mine y) = Mine (x * y) -- needs a to be `Num` how to?
    (Mine x) + (Mine y) = Mine (x + y)
    abs (Mine x) = Mine (abs x)
    signum (Mine x) = Mine (signum x)
    negate (Mine x) = Mine (negate x)
    fromInteger x = Mine x

main = do
    let s=["test1","test2"]
    mapM_ putStr s