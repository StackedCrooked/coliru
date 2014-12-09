tupleXTurn :: [(String, String)]->[(String, String)]
tupleXTurn [] = []
tupleXTurn (x:xs) = (snd x,fst x) : (tupleXTurn xs)

main :: IO ()
main = print $ tupleXTurn [("a","b"),("c","d")]