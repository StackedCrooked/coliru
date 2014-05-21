sum1 = foldr (+) 0

allSum:: (Int -> Int) -> (Int -> Int)
allSum f = \n -> sum1 [ f(x) | x <- [0..n]]

main = putStr . show . allSum (\x -> x + 1) $ 4