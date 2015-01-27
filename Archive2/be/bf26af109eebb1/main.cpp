f :: (Eq a) => a -> [a] -> [a]
f x = filter (== x)

numocc :: (Eq a) => a -> [[a]] -> [Int]
numocc x = map (length . f x)

main :: IO ()
main = print $ numocc 2 [[2, 1, 2], [1, 0, 5], [2, 1, 9, 4]]