factorial :: Integer -> Integer 
factorial 0 = 1
factorial i = foldr (*) 1 [2..i]

inFact :: [Integer]
inFact = map factorial [0..]

main :: IO ()
main = do
    print $ take 10 inFact