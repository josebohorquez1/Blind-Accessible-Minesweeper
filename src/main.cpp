#include <ncurses.h>
#include "Board.h"
void drawBoard(Board& board, int cursor_row, int cursor_col) {
    Tile& tile = board.getTile(cursor_row, cursor_col);
        clear();
        if (tile.is_revealed == false) {
            if (tile.flag_state == false) {
                mvprintw(board.getRows() + 1, 0, "(%d, %d), hidden", cursor_row, cursor_col);
            }
            else {
                mvprintw(board.getRows() + 1, 0, "(%d, %d), hidden, has flag", cursor_row, cursor_col);
            }
        }
        else {
            if (tile.has_mine == false) {
                mvprintw(board.getRows() + 1, 0, "(%d, %d), revealed, %d mines nearby", cursor_row, cursor_col, tile.adjacent_mines);
            }
            else {
                mvprintw(board.getRows() + 1, 0, "(%d, %d), reveal, oh no, a mine", cursor_row, cursor_col);
            }
        }
        refresh();
}
int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    int rows = 10, cols = 10, mines = 30;
    Board board(rows, cols, mines);
    int cursor_row = 0, cursor_col = 0;
    while (true) {
        drawBoard(board, cursor_row, cursor_col);
        int ch = getch();
        switch (ch) {
            case KEY_UP:
            if (cursor_row > 0) --cursor_row;
            break;
            case KEY_DOWN:
            if (cursor_row < rows - 1) ++cursor_row;
            break;
            case KEY_LEFT:
            if (cursor_col > 0) --cursor_col;
            break;
            case KEY_RIGHT:
            if (cursor_col < cols - 1) ++cursor_col;
            break;
            case '\n':
            board.revealTile(cursor_row, cursor_col);
            if (board.checkIfLost()) {
                mvprintw(rows + 2, 0, "You hit a mine! Game over.");
                refresh();
                getch();
                endwin();
                return 0;
            }
            if (board.checkIfWin()) {
                mvprintw(rows + 2, 0, "Congratulations! You win!");
                refresh();
                getch();
                endwin();
                return 0;
            }
            break;
            case ' ':
            board.toggleFlagState(cursor_row, cursor_col);
            break;
            case 'q':
            endwin();
            return 0;
        }
    }
    endwin();
    return 0;
}
