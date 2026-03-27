#ifdef defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
using namespace std;

// ANSI escape code for resetting colors
#define RESET_COLOR "\033[0m"

// ANSI escape codes for text colors
#define BLACK_TEXT "\033[38;5;0m"
#define ORANGE_TEXT "\033[38;5;1m"
#define EMERALD_TEXT "\033[38;5;2m"
#define LIGHT_YELLOW_TEXT "\033[38;5;3m"
#define CYAN_TEXT "\033[38;5;4m"
#define HELIO_TEXT "\033[38;5;5m"
#define JUNGLE_TEXT "\033[38;5;6m"
#define SMOKE_TEXT "\033[38;5;7m"
#define IRON_TEXT "\033[38;5;8m"
#define TANGERINE_TEXT "\033[38;5;9m"
#define MINT_TEXT "\033[38;5;10m"
#define LEMON_TEXT "\033[38;5;11m"
#define OLYMPIC_TEXT "\033[38;5;12m"
#define PINK_TEXT "\033[38;5;13m"
#define SKY_TEXT "\033[38;5;14m"
#define WHITE_TEXT "\033[38;5;15m"
#define SAPPHIRE_TEXT "\033[38;5;21m"
#define AZURE_TEXT "\033[38;5;27m"
#define FERN_TEXT "\033[38;5;28m"
#define BLUE_TEXT "\033[38;5;33m"
#define DARK_GREEN_TEXT "\033[38;5;34m"
#define GREEN_TEXT "\033[38;5;46m"
#define CHILLI_TEXT "\033[38;5;88m"
#define MAGENTA_TEXT "\033[38;5;90m"
#define PURPLE_TEXT "\033[38;5;105m"
#define GRAPE_TEXT "\033[38;5;135m"
#define BROWN_TEXT "\033[38;5;136m"
#define OLIVE_TEXT "\033[38;5;148m"
#define LIME_TEXT "\033[38;5;155m"
#define BABY_TEXT "\033[38;5;159m"
#define DARK_RED_TEXT "\033[38;5;160m"
#define RUSSET_TEXT "\033[38;5;172m"
#define PEANUT_TEXT "\033[38;5;178m"
#define LAGUAN_TEXT "\033[38;5;190m"
#define RED_TEXT "\033[38;5;196m"
#define VIOLET_TEXT "\033[38;5;201m"
#define CARROT_TEXT "\033[38;5;208m"
#define BRICK_TEXT "\033[38;5;210m"
#define AMETHYST_TEXT "\033[38;5;213m"
#define HONEY_TEXT "\033[38;5;214m"
#define YELLOW_TEXT "\033[38;5;220m"
#define CARNATION_TEXT "\033[38;5;225m"
#define ROYAL_TEXT "\033[38;5;226m"
#define GREY_TEXT "\033[38;5;247m"

// ANSI escape codes for background colors
#define BG_BLACK_TEXT "\033[1;40m"
#define BG_RED_TEXT "\033[1;41m"
#define BG_GREEN_TEXT "\033[1;42m"
#define BG_YELLOW_TEXT "\033[1;43m"
#define BG_BLUE_TEXT "\033[1;44m"
#define BG_MAGENTA_TEXT "\033[1;45m"
#define BG_CYAN_TEXT "\033[1;46m"
#define BG_WHITE_TEXT "\033[1;47m"

// Enum for different colors
enum COLOR
{
  BLACK,
  ORANGE,
  EMERALD,
  LIGHT_YELLOW,
  CYAN,
  HELIO,
  JUNGLE,
  SMOKE,
  IRON,
  TANGERINE,
  MINT,
  LEMON,
  OLYMPIC,
  PINK,
  SKY,
  WHITE,
  SAPPHIRE,
  AZURE,
  FERN,
  BLUE,
  DARK_GREEN,
  GREEN,
  CHILLI,
  MAGENTA,
  PURPLE,
  GRAPE,
  BROWN,
  OLIVE,
  LIME,
  BABY,
  DARK_RED,
  RUSSET,
  PEANUT,
  LAGUAN,
  RED,
  VIOLET,
  CARROT,
  BRICK,
  AMETHYST,
  HONEY,
  YELLOW,
  CARNATION,
  ROYAL,
  GREY,
  REMOVE
};

// For Text color
void text_color(COLOR color)
{
  switch (color)
  {
  case BLACK:
    cout << BLACK_TEXT;
    break;
  case ORANGE:
    cout << ORANGE_TEXT;
    break;
  case EMERALD:
    cout << EMERALD_TEXT;
    break;
  case LIGHT_YELLOW:
    cout << LIGHT_YELLOW_TEXT;
    break;
  case CYAN:
    cout << CYAN_TEXT;
    break;
  case HELIO:
    cout << HELIO_TEXT;
    break;
  case JUNGLE:
    cout << JUNGLE_TEXT;
    break;
  case SMOKE:
    cout << SMOKE_TEXT;
    break;
  case IRON:
    cout << IRON_TEXT;
    break;
  case TANGERINE:
    cout << TANGERINE_TEXT;
    break;
  case MINT:
    cout << MINT_TEXT;
    break;
  case LEMON:
    cout << LEMON_TEXT;
    break;
  case OLYMPIC:
    cout << OLYMPIC_TEXT;
    break;
  case PINK:
    cout << PINK_TEXT;
    break;
  case SKY:
    cout << SKY_TEXT;
    break;
  case WHITE:
    cout << WHITE_TEXT;
    break;
  case SAPPHIRE:
    cout << SAPPHIRE_TEXT;
    break;
  case AZURE:
    cout << AZURE_TEXT;
    break;
  case FERN:
    cout << FERN_TEXT;
    break;
  case BLUE:
    cout << BLUE_TEXT;
    break;
  case DARK_GREEN:
    cout << DARK_GREEN_TEXT;
    break;
  case GREEN:
    cout << GREEN_TEXT;
    break;
  case CHILLI:
    cout << CHILLI_TEXT;
    break;
  case MAGENTA:
    cout << MAGENTA_TEXT;
    break;
  case PURPLE:
    cout << PURPLE_TEXT;
    break;
  case GRAPE:
    cout << GRAPE_TEXT;
    break;
  case BROWN:
    cout << BROWN_TEXT;
    break;
  case OLIVE:
    cout << OLIVE_TEXT;
    break;
  case LIME:
    cout << LIME_TEXT;
    break;
  case BABY:
    cout << BABY_TEXT;
    break;
  case DARK_RED:
    cout << DARK_RED_TEXT;
    break;
  case RUSSET:
    cout << RUSSET_TEXT;
    break;
  case PEANUT:
    cout << PEANUT_TEXT;
    break;
  case LAGUAN:
    cout << LAGUAN_TEXT;
    break;
  case RED:
    cout << RED_TEXT;
    break;
  case VIOLET:
    cout << VIOLET_TEXT;
    break;
  case CARROT:
    cout << CARROT_TEXT;
    break;
  case BRICK:
    cout << BRICK_TEXT;
    break;
  case AMETHYST:
    cout << AMETHYST_TEXT;
    break;
  case HONEY:
    cout << HONEY_TEXT;
    break;
  case YELLOW:
    cout << YELLOW_TEXT;
    break;
  case CARNATION:
    cout << CARNATION_TEXT;
    break;
  case ROYAL:
    cout << ROYAL_TEXT;
    break;
  case GREY:
    cout << GREY_TEXT;
    break;
  case REMOVE:
    cout << RESET_COLOR;
    break;
  default:
    break;
  }
}

// For Background colors
void background_color(COLOR color)
{
  switch (color)
  {
  case BLACK:
    cout << BG_BLACK_TEXT;
    break;
  case RED:
    cout << BG_RED_TEXT;
    break;
  case GREEN:
    cout << BG_GREEN_TEXT;
    break;
  case YELLOW:
    cout << BG_YELLOW_TEXT;
    break;
  case BLUE:
    cout << BG_BLUE_TEXT;
    break;
  case MAGENTA:
    cout << BG_MAGENTA_TEXT;
    break;
  case CYAN:
    cout << BG_CYAN_TEXT;
    break;
  case WHITE:
    cout << BG_WHITE_TEXT;
    break;
  case REMOVE:
    cout << RESET_COLOR;
    break;
  default:
    break;
  }
}

// int getch_echo(bool echo = true)
// {
//   struct termios oldt, newt;
//   int ch;
//   tcgetattr(STDIN_FILENO, &oldt);
//   newt = oldt;
//   newt.c_lflag &= ~ICANON;
//   if (echo)
//     newt.c_lflag &= ECHO;
//   else
//     newt.c_lflag &= ~ECHO;
//   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//   ch = getchar();
//   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//   return ch;
// }

// For getting input without printing and pressing enter button on console/terminal
char getch()
{
  char buf = 0;
  struct termios old = {0};
  fflush(stdout);
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  return buf;
}

// For getting input without pressing enter button on console/terminal
char getche()
{
  char buf = 0;
  struct termios old = {0};
  fflush(stdout);

  if (tcgetattr(0, &old) < 0)
    perror("tcgetattr()");

  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;

  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;

  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");

  if (read(0, &buf, 1) < 0)
    perror("read()");

  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");

  printf("%c", buf); // Echo the character back to the console
  fflush(stdout);

  return buf;
}

int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if (ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}
#endif