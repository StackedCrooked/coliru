fibonacci :: [Int]
fibonacci = zipWith (+) (1:fibonacci) (0:1:fibonacci)

main :: IO ()
main = print $ take 10 $ fibonacci