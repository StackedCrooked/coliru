import Data.List (intersect)

main :: IO ()
main = result ["a", "b"] ["a"]

compareList :: (Eq a) => [a] -> [a] -> Bool
compareList a = null . intersect a

result :: (Eq a) => [a] -> [a] -> IO ()
result list1 list2 = 
    if (compareList list1 list2)
        then putStrLn ("They share elements")
        else putStrLn ("They don't share elements")