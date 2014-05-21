import qualified Control.Exception as E

myAction :: IO (Bool)
myAction = return True

main = catchError (do  b <- myAction
                    if b then putStr "True" else putStr "False")
               (\_ -> putStr "opps")