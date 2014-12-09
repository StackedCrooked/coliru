tupelXTurn :: [(String,String)]->[(String,String)]
tupelXTurn [] = []
tupelXTurn (x:xs) = (snd x,fst x) : (tupelXTurn xs)

main :: IO ()
main = print $ tupelXTurn [("a","b"),("c","d")]