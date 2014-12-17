allSubs :: Int -> String -> [String]
allSubs n s = allSubs' (length s) n s
    where allSubs' :: Int -> Int -> String -> [String]
          allSubs' l n s
              | l >= n    = take n s : allSubs' (l - 1) n (tail s)
              | otherwise = []

main :: IO ()
main = print $ allSubs 3 "ABCDEFGH"