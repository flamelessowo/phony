#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define player 'f'

int main (int argc, char *argv[])
{
  int x = 11; int y = 11;
  initscr();
  noecho();
  cbreak();
  curs_set(0);

  WINDOW *win = newwin(0,0,0,0);
  box(win, 0, 0);
  mvwaddch(win, x, y, player);
  refresh();
  wrefresh(win);
  keypad(stdscr, true);
  int typed; 
  while ((typed = getch())) {
    switch(typed) {
      case KEY_DOWN:
        x++;
        break;
      case KEY_UP:
        x--;
        break;
      case KEY_LEFT:
        y--;
        break;
      case KEY_RIGHT:
        y++;
        break;
    }
    wclear(win);
    box(win, 0, 0);
    mvwaddch(win, x, y, player);
    refresh();
    wrefresh(win);
  }
  endwin();
  return 0;
}
