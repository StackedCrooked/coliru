countEven :: Integral a => [a] -> Int
countEven [] = 0
countEven (x:xs) = if even x then (countEven xs) + 1 else countEven xs

main :: IO ()
main = print $ countEven [1..15]