data CTree a b =
        CNode (CTree a b) b (CTree a b) | -- left, value, right
        CLeaf a                           -- value
    deriving (Show, Eq)

instance (Ord a, Ord b) => Ord (CTree a b) where
    (CNode left1 v1 right1) `compare` (CNode left2 v2 right2) =
        if (v1 == v2) then
            if (left1 == left2) then
                (right1 `compare` right2)
            else
                (left1 `compare` left2)
        else v1 `compare` v2

main = do
    print "foo"