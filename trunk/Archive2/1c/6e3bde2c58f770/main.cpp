{-# LANGUAGE ExistentialQuantification #-}

class Renderer a where
    render :: a -> IO ()

data RendererI = forall a. (Renderer a) => RendererImpl a

instance Renderer RendererI where
    render (RendererImpl a) = render a

data Shape = Square { internalData :: Int } | Circle | Rectangle

instance Renderer Shape where
    render (Square x) = putStr ("square: " ++ show x ++ "\n")
    render Circle = putStr "circle\n"
    render Rectangle = putStr "rect\n"

main :: IO ()
main = do
    render (RendererImpl (Square 1))
    render (RendererImpl Circle)
    render (RendererImpl (Square 666))
    
