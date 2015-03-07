myLength :: [a]  -> Int
myLength x = 
    let innerLength :: [a] -> Int -> Int  -- Tail recursive inner call
        innerLength [] n      = n
        innerLength (x:xs) n  = innerLength xs (n+1)
    in innerLength x 0

main :: IO ()
main = print $ myLength [1, 2, 3]