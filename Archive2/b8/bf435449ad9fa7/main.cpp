factorial :: Integer -> Integer 
factorial i = foldr (*) 1 [2..i]

inFact :: [Integer]
inFact = map factorial [1..]

main :: IO ()
main = do
    print $ take 10 inFact