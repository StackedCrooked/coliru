myLength :: [a]  -> Int
myLength x = innerLength x 0
    where innerLength :: [a] -> Int -> Int  -- Tail recursive inner call
          innerLength [] n      = n
          innerLength (x:xs) n  = innerLength xs (n+1)

main :: IO ()
main = print $ myLength [1, 2, 3]