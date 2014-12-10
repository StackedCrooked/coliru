countEven :: Integral a => [a] -> Int
countEven = length . filter even

main :: IO ()
main = print $ countEven [1..15]