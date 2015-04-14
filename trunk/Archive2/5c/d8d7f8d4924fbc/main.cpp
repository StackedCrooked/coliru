data Box = forall a. (Show a) => Box a

instance Show Box where
    show (Box x) = show x

polyTail :: [a] -> Maybe [a]
polyTail [] = Nothing
polyTail (_:xs) = Just xs

main :: IO ()
main = print $ polyTail [Box 1, Box 12.0, Box "Three"]