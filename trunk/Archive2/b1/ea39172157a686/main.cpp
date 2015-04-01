data Rec t = Rec { inside :: (t Int) }

class SomeClass t where
    def :: Rec t
    
instance SomeClass Maybe where
    def = Rec (Just 31)
    
instance SomeClass IO where
    def = Rec (return 31)
    
myDef :: Rec Maybe
myDef = def { inside = Nothing }
    
main :: IO ()
main = putStr "ok" 