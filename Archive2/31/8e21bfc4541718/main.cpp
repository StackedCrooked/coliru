tupelXTurn :: [(String,String)]->[(String,String)]
tupelXTurn (x:xs) = (snd x,fst x) : (tupelXTurn xs)

main :: IO ()
main = print "ok"