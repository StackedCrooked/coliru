import Data.List (maximumBy)

type MakeUp = (String, String, Int)

stuff :: [MakeUp]
stuff = [("eye liner","MAC",250),("foundation","YSL",800),("toner","GIVENCHY",700),("lip gloss","BENEFIT",900),("bronzer","BENEFIT",500)]

listAllSold :: String -> [MakeUp] -> [MakeUp] 
listAllSold nameOfBrand = filter (\(_, n, _) -> n == nameOfBrand)

mostSold :: [MakeUp] -> MakeUp
mostSold = maximumBy (\(_, _, a) (_, _, b) -> compare a b)

main :: IO ()
main = do
    print $ listAllSold "BENEFIT" stuff
    print $ mostSold stuff