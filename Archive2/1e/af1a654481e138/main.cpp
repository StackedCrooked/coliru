import Data.List (sortBy)
import Data.Function (on)

getnames :: (Double, [Int]) -> [String] -> (Double, [Int], [String])
getnames (dbl, ixes) names = 
    let srtLst = map (names !!) ixes in
    (dbl, ixes, srtLst)

main :: IO ()
main = print $ getnames (41.12, [1,2,3,0]) ["pete","ben","bill","bob"]
