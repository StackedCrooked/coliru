enum GameType {};

#ifndef GRIDGAME_H
#define GRIDGAME_H

//#include "GameType.h"

class GridGame {
public:
    GridGame();

    ~GridGame();

    enum GameType GetType() { return m_type; }

    void OutputGreeting() const;

    int NumPlayers() const;

    char GetPlayerSymbol(int player) const;

    int GetBoardSize() const;

    /* Returns NULL on good move, else returns err string.
     * Note that this check is game-neutral (at least for TTT and Reversi)
     */
    const char *IsLegalMove(int player, int row, int col) const;

    void OutputBoard() const;


protected:
    GridGame(enum GameType type, const char *name, const char *playerSymbols, int boardSize);

    void DoBasicMove(int player, int row, int col);

    // The only data member that the subclassed games should really
    // need full read/write access to, once game is set up.
    char **m_board;

private:
    enum GameType m_type;
    const char *m_gameName;
    int m_boardSize;
    const char *m_playerSymbols;

};

#endif //GRIDGAME_H

int main() {}