#include "Board.h"
Board::Board(int rows, int cols, int num_mines) {
    this->rows = rows;
    this->cols = cols;
    this->num_mines = num_mines;
    initializeBoard();
    randomizeMines();
    findAllSurroundingTiles();
}
void Board::initializeBoard() {
    for (unsigned row = 0; row < rows; ++row) {
        std::vector<Tile> row_vec;
        for (unsigned int col = 0; col < cols; ++col) {
            Tile tile;
            tile.flag_state = false;
            tile.has_mine = false;
            tile.is_revealed = false;
            row_vec.push_back(tile);
        }
        tiles.push_back(row_vec);
    }
}
void Board::randomizeMines() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> row_dist(0, rows - 1);
    std::uniform_int_distribution<int> col_dist(0, cols - 1);
    int mines_placed = 0;
    while (mines_placed < num_mines) {
        int row = row_dist(gen);
            int col = col_dist(gen);
        if (tiles[row][col].has_mine == false) {
            tiles[row][col].has_mine = true;
            mines_placed++;
        }
    }
}
void Board::findAllSurroundingTiles() {
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (unsigned int row = 0; row < tiles.size(); ++row) {
        for (unsigned int col = 0; col < tiles[row].size(); ++col) {
            for (unsigned int i = 0; i < 8; ++i) {
                int next_row = row + dr[i];
                int next_col = col + dc[i];
                if ((next_row >= 0 && next_row < rows) && (next_col >= 0 && next_col < cols)) {
                    Tile* ptr = &tiles[next_row][next_col];
                    if (ptr->has_mine == true) {
                        tiles[row][col].adjacent_mines += 1;
                    }
                    tiles[row][col].adjacent_tiles.push_back(ptr);
                }
            }
        }
    }
}
void Board::revealTile(int row, int col) {
    if (tiles[row][col].is_revealed == true) {
        return;
    }
    tiles[row][col].is_revealed = true;
        if (tiles[row][col].adjacent_mines == 0) {
            int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            for (unsigned int i = 0; i < 8; ++i) {
                int next_row = row+ dr[i];
                int next_col = col + dc[i];
                if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols) {
                    revealTile(next_row, next_col);
            }
        }
}
}
void Board::toggleFlagState(int row, int col) {
    tiles[row][col].flag_state = !tiles[row][col].flag_state;
}
bool Board::checkIfWin() {
    for (unsigned int row = 0; row < tiles.size(); ++row) {
        for (unsigned int col = 0; col < tiles[row].size(); ++col) {
            if (tiles[row][col].is_revealed == false && tiles[row][col].has_mine == true) {
                return false;
            }
        }
    }
    return true;
}
bool Board::checkIfLost() {
    for (unsigned int row = 0; row < tiles.size(); ++row) {
        for (unsigned int col = 0; col < tiles[row].size(); ++col) {
            if (tiles[row][col].has_mine == true && tiles[row][col].is_revealed == true) {
                return true;
            }
        }
    }
    return false;
}
void Board::reset() {
    tiles.clear();
    initializeBoard();
    randomizeMines();
    findAllSurroundingTiles();
}
Tile& Board::getTile(int row, int col) {
    return tiles[row][col];
}
int Board::getRows() {
    return rows;
}
int Board::getCols() {
    return cols;
}
