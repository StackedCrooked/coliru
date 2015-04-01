data Shape = Square { something :: Int } | Circle

class Renderer a where
    initial :: a
    render :: (Renderer a) => a -> Shape -> IO ()
    
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

foo s = render (initial :: RendererFoo) s
bar s = render (initial :: RendererBar) s

renderSpecial :: (Shape -> IO ()) -> IO ()
renderSpecial r = r (Square 666)

thingies :: [Shape]
thingies = [Square 123, Circle]
renderers :: [Shape -> IO ()]
renderers = [foo, bar]
    
main :: IO ()
main = do
    mapM_ (\renderer -> mapM_ renderer thingies) renderers
    renderSpecial foo
