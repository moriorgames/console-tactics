#include <ncurses.h>

#define ANSI_BLOCK      "\u2588"
#define ANSI_LIGHT      "\u2591"
#define ANSI_MEDIUM     "\u2592"
#define ANSI_DARK       "\u2593"

int main()
{
//    initscr();
//    start_color();
//
//    init_pair(1, COLOR_BLACK, COLOR_RED);
//    init_pair(2, COLOR_BLACK, COLOR_GREEN);
//
//    attron(COLOR_PAIR(1));
//    printw("This should be printed in black with a red background!\n");
//
//    attron(COLOR_PAIR(2));
//    printw("And this in a green background!\n");
//    refresh();
//
//    getch();
//
//    endwin();



    int lines = 40, cols = 120, y0 = 0, x0 = 0;
    bool finished = false;
    initscr();
    WINDOW *win = newwin(lines, cols, y0, x0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_GREEN);

    while (!finished) {

        auto keyInput = getch();
        if (keyInput == ERR) {
            continue;         /* ignore when there was a timeout - no data */
        } else if (keyInput == 'q' || keyInput == 'Q') {
            finished = true;
        }
//        attron(COLOR_PAIR(1));
        for (int i = 0; i < lines; ++i) {
            for (int j = 0; j < cols; ++j) {
                mvwaddch(win, i, j, ACS_DIAMOND | COLOR_PAIR(1));
            }
        }
//        attroff(COLOR_PAIR(1));

        wrefresh(win);
    }

    endwin();

    return 0;
}

