import qualified Control.Exception as E

myAction :: IO (Bool)
myAction = fail "foo"

main = E.catch (do  b <- myAction
                    if b then putStr "True" else putStr "False")
               handler
       where handler :: IOError -> IO ()
             handler _ = putStr "opps"