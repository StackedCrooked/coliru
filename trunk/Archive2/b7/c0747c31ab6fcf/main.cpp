import Data.Map as M

messages :: M.Map Int String
messages = 
    M.fromList
        [ (200, "...")
        , (404, "...")
        ]

main = return ()