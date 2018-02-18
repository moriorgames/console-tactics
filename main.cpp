
#include <ncurses.h>

int main()
{
    int lines = 40, cols = 120, y0 = 0, x0 = 0;
    bool finished = false;
    initscr();
    start_color();

    WINDOW *win = newwin(lines, cols, y0, x0);
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_BLUE, COLOR_GREEN);
    wtimeout(win, 100);

    int count = 0;
    while (!finished) {

        for (int i = 0; i < lines; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (count % 2 == 0) {
                    mvwaddch(win, i, j, '#' | COLOR_PAIR(1));
                }  else {
                    mvwaddch(win, i, j, '#' | COLOR_PAIR(2));
                }
            }
        }

        wrefresh(win);
        count++;

        auto keyInput = wgetch(win);
        if (keyInput == ERR) {
            continue;         /* ignore when there was a timeout - no data */
        } else if (keyInput == 'q' || keyInput == 'Q') {
            finished = true;
        }
    }

    endwin();

    return 0;
}
