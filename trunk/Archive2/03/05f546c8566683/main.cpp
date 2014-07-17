fetchSomething :: IO String
fetchSomething = return "Something"

main :: IO ()
main = do
    if True
        then do
            l <- fetchSomething
            let fn s = do
                let rs = s ++ ": "
                l <- fetchSomething
                return $ rs ++ l
            n <- fn "Prefix"
            putStr n
        else return ()
        
{-
    let ep = Bridge.destination b </> e
    ed <- doesDirectoryExist ep
    if ed 
        then do
            ds <- listDirs ep
            let fn p = do
                let t = readUTC p
                lt <- toLocalTime t               <-- parse error (possibly incorrect indentation or mismatched brackets)
                return $ Snapshot t lt e b 
            l <- mapM fn ds
            let r = sortBy (compare `on` time) l
            let ri = Prelude.take m $ assignIDs 1 r
            if o == Oldest
                then return $ ri
                else return $ reverse ri
        else return []
-}