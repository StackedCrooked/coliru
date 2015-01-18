leftFolder :: (a -> b -> a) -> a -> [b] -> a
leftFolder _ c [] = c
leftFolder fn c (x:xs) = 
    leftFolder fn (fn c x) xs

main :: IO ()
main = print $ leftFolder (-) 10 [1, 2, 3]