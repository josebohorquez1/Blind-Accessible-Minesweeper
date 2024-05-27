#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <random>
struct Tile {
    bool is_revealed;
    bool flag_state;
    bool has_mine;
    int adjacent_mines = 0;
    std::vector<Tile*> adjacent_tiles;
};
class Board {
private:
    int rows;
    int cols;
    int num_mines;
    std::vector<std::vector<Tile>> tiles;
    void initializeBoard();
    void randomizeMines();
    void findAllSurroundingTiles();
        void findAdjacentMines();
public:
    Board(int rows, int cols, int num_mines);
    void revealTile(int row, int col);
    void toggleFlagState(int row, int col);
    bool checkIfWin();
    bool checkIfLost();
    void reset();
    Tile& getTile(int row, int col);
    int getRows();
    int getCols();
};

#endif