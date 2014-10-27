con :: Int -> Bool
con = (== 1)

main :: IO ()
main = do
    print $ con (length [1])
    print $ con (length [1, 2])