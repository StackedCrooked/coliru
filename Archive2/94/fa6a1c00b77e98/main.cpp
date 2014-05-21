import Data.Map as M

messages :: M.Map Int String
messages = 
    M.fromList
        [ (200, "200")
        , (404, "404")
        ]

main = do
    let m = M.lookup 200 messages
    case m of
        Just s -> putStrLn s
        Nothing -> return ()