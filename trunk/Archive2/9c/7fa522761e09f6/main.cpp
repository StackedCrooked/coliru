testInput :: String
testInput = "2000\nbooka 500\n\nbookb 1000\n\nbookc 250\n\nbookd 250"

readTotal :: String -> Double
readTotal = read

readPart :: String -> (String, Double)
readPart s = 
    let (x:y:[]) = words s
    in  (x, read y)
        
calcPercentage :: Double -> (String, Double) -> (String, Double)
calcPercentage total (l, a) = (l, (a / total) * 100)
        
showPercentage :: (String, Double) -> String
showPercentage (l, a) = concat [l, " ", show a, "%\n"]

main :: IO ()
main = do
    let fileLines       = lines testInput
        nonEmptyLines   = filter (/= "") fileLines
        total = readTotal . head $ nonEmptyLines
        parts = map readPart . tail $ nonEmptyLines
    mapM_ (putStr . showPercentage) (map (calcPercentage total) parts)