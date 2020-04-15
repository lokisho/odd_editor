#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode); // call when the program exists.
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON); // ICANON will read byte by byte instead of line by line.
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main() {
  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
  std::cout << "Hello World4!" << "\n";
  return 0;
}
