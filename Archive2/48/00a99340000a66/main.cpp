data ErrorCatA = WTFError String | OMGError String
data ErrorCatB = BadError Int | TerribleError Float

class GError a where
    errorMessage :: a -> String
    
instance GError ErrorCatA where
    errorMessage (WTFError s) = "WTF?! " ++ s
    errorMessage (OMGError s) = "OMG?! " ++ s

instance GError ErrorCatB where
    errorMessage (BadError i)      = "Bad! " ++ show i
    errorMessage (TerribleError f) =  "Terrible! " ++ show f
    
handleError :: GError a => a -> IO ()
handleError = putStrLn . errorMessage

main = handleError $ WTFError "ok"