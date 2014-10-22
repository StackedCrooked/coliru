main :: IO ()
main = do
    print $ take 10 $ inFact
    
factorial :: Integer -> Integer 
factorial i = foldr (*) 1 [2..i]

inFact :: [Integer]
inFact = map (\i -> factorial i) [1..]