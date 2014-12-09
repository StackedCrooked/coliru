import Data.Tuple (swap)

tupelXTurn :: [(String,String)]->[(String,String)]
tupelXTurn = map swap

main :: IO ()
main = print $ tupelXTurn [("a","b"),("c","d")]