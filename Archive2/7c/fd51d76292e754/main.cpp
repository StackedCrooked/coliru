type Position = (Int, Int)

-- input comes from whatever place
data Input = Input { mouseClick :: Bool } 

-- all the entities of your world
data Object = Box Position | Tree Position

-- game state keeps track of the object in the world
-- as well as points or anything the game doesn't share with any
-- particular view
data GameState =
    Gamestate
        { objects :: [Object] }

placeObj :: GameState -> GameState
placeObj = undefined -- bla bla bla

handleInput :: Input -> GameState -> GameState
handleInput (Input clicked) gstate =
    if clicked
        then placeObj (34, 56) gstate
        else gstate
        
draw :: GameState -> IO ()
draw (GameState objs) = do
    mapM_ (drawPolymorphic) objs