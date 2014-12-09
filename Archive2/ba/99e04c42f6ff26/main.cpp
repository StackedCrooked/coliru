import Data.Tuple (swap)

tupleXTurn :: [(a, b)]->[(b, a)]
tupleXTurn = map swap

main :: IO ()
main = print $ tupleXTurn [("a","b"),("c","d")]