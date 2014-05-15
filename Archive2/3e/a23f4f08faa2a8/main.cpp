import Data.Tuple

reversedTuple = flip (,)

main = putStr $ fst $ reversedTuple "First" "Second"