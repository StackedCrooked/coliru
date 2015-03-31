class SomeClass t where
    type CacheType
    iDon'tKnow :: t -> CacheType
    
instance SomeClass Int where
    type CacheType = (Int, Int)
    iDon'tKnow i = (i, i)
    
main :: IO ()
main = putStr "ok"