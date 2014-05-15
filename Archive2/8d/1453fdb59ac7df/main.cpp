reversedTuple = flip (,)

main = putStr $ fst $ reversedTuple "First" "Second"