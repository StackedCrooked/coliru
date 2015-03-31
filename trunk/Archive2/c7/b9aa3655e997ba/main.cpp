{-# LANGUAGE ExistentialQuantification #-}

data Shape = Square { something :: Int } | Circle

class Renderer a where
    render :: (Renderer a) => a -> Shape -> IO ()

data RendererI = forall a. (Renderer a) => RendererImpl a

instance Renderer RendererI where
    render (RendererImpl a) x = render a x
    
data RendererFoo = Foo { internalData :: Int }

instance Renderer RendererFoo where
    render r (Square x) = putStr ("square: " ++ (show x) ++ "\n")
    render r Circle = putStr ("circle, internalData: " ++ show (internalData r) ++ "\n")
    
data RendererBar = Bar { uglyData :: Int }

instance Renderer RendererBar where
    render r (Square x) = putStr ("square: " ++ (show x) ++ "\n")
    render r Circle = putStr ("circle, uglyData: " ++ show (uglyData r) ++ "\n")

foo = RendererImpl (Foo 100)
bar = RendererImpl (Bar 300)
    
main :: IO ()
main = do
    render foo (Square 123)
    render foo Circle
    render bar (Square 321)
    render bar Circle
