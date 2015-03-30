{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE FlexibleContexts #-}

module Main where

import Control.Monad.State
import Control.Monad.IO.Class

-- Module
----------------------------------------------------------------------------------------
newtype Module m a b =
    Module (a -> m (b, Module m a b))

{-
instance (Monad m) => Applicative (Module m a)
instance (Monad m) => Arrow (Module m)
instance (Monad m) => Category (Module m)
instance (Monad m) => Functor (Module m a)
-}

-- GraphicsModule
----------------------------------------------------------------------------------------
data GraphicsState = GraphicsState Int

render :: (MonadState GraphicsState m, MonadIO m) => Int -> m ()
render x = do
    (GraphicsState s) <- get
    liftIO $ print $ x + s
    put . GraphicsState $ s + 1

type GraphicsModule = Module IO Int ()

initialGraphicsState = GraphicsState 0

createGraphicsModule :: GraphicsState -> GraphicsModule 
createGraphicsModule initialState = Module $ \x -> do
    (r, s') <- runStateT (render x) initialState
    return (r, createGraphicsModule s') 

runModule (Module m) x = m x

-- Program
----------------------------------------------------------------------------------------
data ProgramState = ProgramState {
    graphicsModule :: GraphicsModule
}

renderInProgram :: (MonadState ProgramState m, MonadIO m) => Int -> m ()
renderInProgram x = do
    gm <- gets graphicsModule
    (r, gm') <- liftIO $ runModule gm x
    
    modify $ \g -> g { graphicsModule = gm' }
    
initialProgramState = ProgramState (createGraphicsModule initialGraphicsState)

main = runStateT prog initialProgramState

prog = do
    renderInProgram 1
    renderInProgram 1
    renderInProgram 1
    
    
