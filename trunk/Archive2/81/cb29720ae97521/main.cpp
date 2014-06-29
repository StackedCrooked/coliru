import Data.Map (Map)
import qualified Data.Map as Map

countDistinct :: Ord a => [a] -> Int
countDistinct ls = Map.size $ foldr fn Map.empty ls
    where fn e m = Map.insertWith (+) e 1 m

b :: String -> Bool
b s = countDistinct s `elem` [1, 2, 3]

c :: [String]
c = filter b $ do
    a <- ['0'..'9']
    b <- ['0'..'9']
    c <- ['0'..'9']
    d <- ['0'..'9']
    return $ a:b:c:d:[]

main :: IO ()
main = mapM_ putStrLn c