allSubs :: Int -> String -> [String]
allSubs n s
    | length s >= n = take n s : allSubs n (tail s)
    | otherwise = []

main :: IO ()
main = print $ allSubs 3 "ABCDEFGH"