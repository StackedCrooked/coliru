{-# LANGUAGE ExistentialQuantification #-}

class Renderer a where
    render :: a -> IO ()

data RendererI = forall a. (Renderer a) => RendererImpl a

instance Renderer RendererI where
    render (RendererImpl a) = render a

data Shape = Square | Circle | Rectangle

instance Renderer Shape where
    render Square = putStr "square"
    render Circle = putStr "circle"
    render Rectangle = putStr "rect"

main :: IO ()
main = do
    render (RendererImpl Square)
