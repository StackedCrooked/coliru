data Item = X Int | Y Char deriving (Eq, Show)

specialReplace :: Item -> Item -> Item
specialReplace toReplace (X _) = toReplace
specialReplace toReplace y     = y

main :: IO ()
main = do
    let a = [X 1, Y 'g']
    let b = (X 2)
    print $ map (specialReplace b) a