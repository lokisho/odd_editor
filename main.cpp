#include <cstdio>
#include <cctype>
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
  // IXON Disables ctrl+s y ctrl+q
  // ICRNL outputs ctrl+m to 13. By default, it has a weird behavior that outputs 10
  raw.c_iflag &= ~(ICRNL | IXON);
  // Disables \n and \r\n.
  // in our program we’ll have to write out the full "\r\n" whenever we want to start a new line
  // endl won't work.
  raw.c_oflag &= ~(OPOST);
  // ICANON will read byte by byte instead of line by line.
  // ISIG will turn off ctrl+z y ctrl + c
  // IEXTEN disables ctrl+v => in terminal that is NOT paste.
  raw.c_lflag &= ~(ECHO | IEXTEN | ICANON | ISIG);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main() {
  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
   if (std::iscntrl(c)) {
      // std::printf("%d\n", c);
      std::cout << (int)c << "\r\n";
    } 
   else {
      // std::printf("%d ('%c')\n", c, c);
      std::cout << (int)c << ' '  << c << "\r\n";
    }
  }
  // Testing the byte by byte printing each character.
   return 0;
}
