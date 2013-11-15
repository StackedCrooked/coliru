ifM :: Monad m => m Bool -> m a -> m a -> m a
ifM m a b = do{ v <- m; if v then a else b }

turn :: Player -> Game (Maybe Player)
turn player = do
  printBoard
  pos <- liftIO $ prompt $ show player ++ "'s move (x,y):"
  let (x, y) = read pos :: (Int, Int)
  ifM (not <$> move player x y)
    (turn player)
    (ifM (playerWon player)
      (return $ Just player)
      (ifM (gets $ all isJust)
        (return Nothing)
        (turn $ flipPlayer player)))