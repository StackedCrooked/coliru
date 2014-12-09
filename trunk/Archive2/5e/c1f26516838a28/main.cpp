import Data.Tuple (swap)

tupelXTurn :: [(a, b)]->[(b, a)]
tupelXTurn = map swap

main :: IO ()
main = print $ tupelXTurn [("a","b"),("c","d")]