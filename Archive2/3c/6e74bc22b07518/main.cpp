myLength :: [a]  -> Int
myLength x = innerLength x 0
    where innerLength :: [a] -> Int -> Int  -- Tail recursive inner call
          innerLength [] _      = 0
          innerLength (x:xs) n  = innerLength xs n+1

main :: IO ()
main = print $ myLength [1, 2, 3]