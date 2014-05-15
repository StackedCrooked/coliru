data CTree a b =
        CNode (CTree a b) b (CTree a b) | -- left, value, right
        CLeaf a                           -- value
    deriving (Show, Eq)

instance (Ord a, Ord b) => Ord (CTree a b) where
    (CNode left1 v1 right1) `compare` (CNode left2 v2 right2) = v1 `compare` v2

main = do
    print "foo"