func :: [Int] -> [Int]
func = fmap (+3)

main = print $ func [1, 2, 3]