reversedTuple :: b -> a -> (a, b)
reversedTuple = flip (,)

main = putStr $ fst $ reversedTuple "First" "Second"