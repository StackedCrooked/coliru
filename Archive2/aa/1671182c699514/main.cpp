  int countIslands() {
    int count = 0;
    
    for (int row = 0; row < numRows; row++) {
      for (int col = 0; col < numCols; col++) {
        pos currPos = pos(row, col);
        
        if (isIsland(currPos) && !isVisited(currPos)) {
          count++;
          findCompleteIslandDFS(currPos);
        }
      }
    }
    
    return count;
  }

  void findCompleteIslandDFS(const pos &start) {
    pos currPos = start;
    queue<pos> q;
    q.push(currPos);
    
    while (!q.empty()) {
      currPos = q.front();
      q.pop();
      
      if (!isVisited(currPos)) {
        setVisited(currPos);
      } else {
        continue;
      }

      vector<Direction> moveDirs = {LEFT, RIGHT, UP, DOWN};
      for (auto m : moveDirs) {
        if (canMove(currPos, m)) {
          pos newPos = move(currPos, m);
          q.push(newPos);
        }
      }
    }
  }