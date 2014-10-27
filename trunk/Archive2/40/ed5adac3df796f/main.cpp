con :: [a] -> Bool
con = (== 1) . length

main :: IO ()
main = do
    print $ con [1]
    print $ con [1, 2]