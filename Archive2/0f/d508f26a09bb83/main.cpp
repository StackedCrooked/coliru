data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show)

printTree :: (Show a) => Tree a -> String
printTree (Node a left right) = printTreeAux (Node a left right) 0

printTreeAux :: (Show a) => Tree a -> Int -> String
printTreeAux EmptyTree _ = ""
printTreeAux (Node a left right) depth = (replicate (6 * depth) ' ') ++ show a ++ "\n" ++ (printTreeAux left (depth + 1)) ++ "\n" ++ (printTreeAux right (depth + 1))

main :: IO ()
main = putStr $ printTree (Node 1 (Node 2 EmptyTree EmptyTree) (Node 3 EmptyTree EmptyTree))