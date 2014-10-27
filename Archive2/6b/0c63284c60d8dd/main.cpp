toFahrenheit :: Double -> Double
toFahrenheit celsius = 1.8 * celsius + 32 

weatherLike2 :: Double -> String
weatherLike2 celsius 
    | fahrenheit <=    32  =   "Freezing" 
    | fahrenheit <=    68  =   "So Coold"
    | fahrenheit <=    100 =   "Warming"
    | fahrenheit <=    122 =   "Hot!!"
    | otherwise            =   "As Hell!!" 
    where fahrenheit = toFahrenheit celsius
    
main :: IO ()
main = do
    print $ weatherLike2 33