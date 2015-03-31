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

thingies :: [Shape]
thingies = [Square 123, Circle]
renderers :: [RendererI]
renderers = [foo, bar]
    
main :: IO ()
main = do
    mapM_ (\x -> mapM_ (render x) thingies) renderers
