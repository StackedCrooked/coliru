import Data.Tuple

tuple :: (Int, String)
tuple = (1, "OK")

main = putStr $ (fst . swap) tuple