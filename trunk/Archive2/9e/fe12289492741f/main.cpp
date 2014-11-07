isPalindrome :: String -> Bool
isPalindrome s = reverse s == s

findPalindromes :: String -> [(Int, Int)]
findPalindromes s = foldr (\n palindromes -> palindromes ++ findPalindromesFromOfLength 1 n s) [] [4..12]

findPalindromesFromOfLength :: Int -> Int -> String -> [(Int, Int)]
findPalindromesFromOfLength i l s
    | length s < l || l == 0 = []
    | otherwise =
        if isPalindrome current
            then (i, l) : recursive
            else recursive
        where 
            current = take l s
            recursive = findPalindromesFromOfLength (i + 1) l (drop 1 s)
            
main :: IO ()
main = do
    print $ findPalindromes "ABBALKJAHFDYIOIUUIHKOOOOOKIHUGY"