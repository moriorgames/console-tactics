#include <iostream>

#define ANSI_BLOCK          "\u2588"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

using namespace std;

int main()
{
    cout << ANSI_COLOR_GREEN;
    for (int i = 1; i <= 30; ++i) {
        cout << ANSI_BLOCK;
    }
    cout << ANSI_COLOR_RESET << endl;

    return 0;
}
