countElem :: Eq a => [a] -> a -> Int
countElem ls e = length $ filter (== e) ls

countFrequency :: Eq a => [a] -> [a] -> [(a, Int)]
countFrequency sm ls = map fn sm
    where fn e = (e, countElem e ls)
    
main = print . countFrequency ['A'] $ "GRAAL"