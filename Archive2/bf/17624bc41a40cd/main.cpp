data Promise f a =  PendingPromise f | ResolvedPromise a | BrokenPromise deriving (Show)

instance Monad (Promise f) where
    return a = ResolvedPromise a
    BrokenPromise >>= _ = BrokenPromise
    PendingPromise a >>= _ = PendingPromise a
    ResolvedPromise a >>= f = f a

main = putStr "Compiled!"