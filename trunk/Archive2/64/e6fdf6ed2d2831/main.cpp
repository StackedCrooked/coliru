class HasSome s where
    has :: (Eq a) => a -> s a -> Bool
    
instance HasSome [] where
    has x l = elem x l
    
instance HasSome Maybe where
    has x (Just y) = x == y
    has _ Nothing = False
    
main :: IO ()
main = do
    let f = has 1 -- which one? `Maybe` or `[]`?
    print "ok"