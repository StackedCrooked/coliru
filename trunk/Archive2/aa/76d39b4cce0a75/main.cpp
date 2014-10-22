data Item = X Int | Y Char deriving (Eq, Show)

specialReplace :: Item -> Item -> Item
specialReplace (X x1) (X x2) = (X x1)
specialReplace (Y y1) (Y y2) = (Y y1)
specialReplace _ a = a

main :: IO ()
main = do
    let a = [X 1, Y 'g']
    let b = [X 2]
    print $ foldr (\el list -> map (specialReplace el) list) a b