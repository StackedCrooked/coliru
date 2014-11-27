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

-- intentionally simple
-- here input is analyzed, entities are moved
-- collisions are detected and points are updated
-- (all in specific subfunctions of course, like placeObj)
logic :: Input -> GameState -> GameState
logic (Input clicked) gstate =
    if clicked
        then placeObj (34, 56) gstate
        else gstate

-- here we have the game state at the end of a
-- specific frame, we can just render it
draw :: GameState -> IO ()
draw (GameState objs) = do
    mapM_ (drawPolymorphic) objs
    
main :: IO ()
main = runGame (GameState [])