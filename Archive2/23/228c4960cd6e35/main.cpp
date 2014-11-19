type Something = Int

data Block
    = Para { field :: [Something] }
    | Plain { field :: [Something] }
    deriving (Eq)
    
test :: [Block] -> [Block]
test (x:rest) = x { field = [(field x) !! 0] } : rest
            
main :: IO ()
main = do
    print $ "ok"