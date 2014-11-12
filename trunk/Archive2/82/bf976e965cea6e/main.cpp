import qualified Control.Exception as E

myAction :: IO (Bool)
myAction = return True

main = do
    b <- E.catch (myAction)
                 (\_ -> putStr "opps")
    if b then putStr "True" else "False"