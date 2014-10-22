apply :: Int -> (a -> a) -> a -> a
apply 0 _ = id
apply 1 f = f
apply n f = (apply (n - 1) f) . f

main :: IO ()
main = do
    print $ apply 0 (+1) 0
    print $ apply 1 (+1) 0
    print $ apply 4 (+1) 0
    print $ apply 13 (+3) 0