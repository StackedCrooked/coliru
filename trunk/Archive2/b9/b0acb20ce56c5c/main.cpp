{-# LANGUAGE ExistentialQuantification #-}

data Shape = Square { something :: Int } | Circle

class Renderer a where
    initial :: a
    render :: (Renderer a) => a -> Shape -> IO ()

data RendererI = forall a. (Renderer a) => RendererImpl a

instance Renderer RendererI where
    render (RendererImpl a) x = render a x
    
data RendererFoo = Foo { internalData :: Int }

instance Renderer RendererFoo where
    initial = Foo 100
    render r (Square x) = putStr ("square: " ++ (show x) ++ "\n")
    render r Circle = putStr ("circle, internalData: " ++ show (internalData r) ++ "\n")
    
data RendererBar = Bar { uglyData :: Int }

instance Renderer RendererBar where
    initial = Bar 300
    render r (Square x) = putStr ("square: " ++ (show x) ++ "\n")
    render r Circle = putStr ("circle, uglyData: " ++ show (uglyData r) ++ "\n")

foo = RendererImpl (initial :: RendererFoo)
bar = RendererImpl (initial :: RendererBar)
baz = RendererImpl (initial :: RendererI)

renderSpecial :: RendererI -> IO ()
renderSpecial r = render r (Square 666)

thingies :: [Shape]
thingies = [Square 123, Circle]
renderers :: [RendererI]
renderers = [foo, bar, baz]
    
main :: IO ()
main = do
    mapM_ (\x -> mapM_ (render x) thingies) renderers
    renderSpecial foo
