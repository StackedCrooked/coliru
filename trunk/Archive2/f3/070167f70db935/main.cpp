data CTree a b =
        CNode (CTree a b) b (CTree a b) | -- left, value, right
        CLeaf a                           -- value
    deriving (Show, Eq)

instance (Ord a, Ord b) => Ord (CTree a b) where
    (CNode _ v1 _) `compare` (CNode _ v2 _) = v1 `compare` v2

main = do
    print "foo"