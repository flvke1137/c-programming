/* stage2.c - Arthur's Easter Egg implementation */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define KEYWORD "specter"

/* Easter Egg struct */
struct EasterEgg {
  char keyword[8];  /* "specter" + '\0' */
  char message[512];
};

static struct EasterEgg arthur_egg = {
  .keyword = KEYWORD,
  .message =
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. "
    "I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. "
    "The past Arthur was a ghost of dogmatism and stubbornness."
};

/* Convert char to 8-bit binary string */
static void char_to_binary(char c, char *bin_str)
{
  int i;
  for (i = 7; i >= 0; i--) {
    bin_str[7 - i] = (c & (1 << i)) ? '1' : '0';
  }
  bin_str[8] = '\0';
}

/* Reverse string in place */
static void reverse_str(char *str)
{
  int i, j;
  char tmp;
  int len = (int)strlen(str);
  for (i = 0, j = len - 1; i < j; i++, j--) {
    tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

/* Check if user input matches the keyword */
static int isRightChar(const char *input, const char *keyword)
{
  if (strlen(input) != strlen(keyword))
    return 0;
  for (int i = 0; keyword[i]; i++) {
    if (input[i] != keyword[i])
      return 0;
  }
  return 1;
}

/* Check if user input word matches Easter egg keyword */
static int isEasterEgg(const char *input, const struct EasterEgg *egg)
{
  return strcmp(input, egg->keyword) == 0;
}

/* Flush stdin buffer */
static void flush_stdin(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

/* Read line safely, remove newline */
static void read_line(char *buffer, int size)
{
  if (fgets(buffer, size, stdin) != NULL) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
      buffer[len - 1] = '\0';
    else
      flush_stdin();
  }
}

/* Easter egg main function */
static void find_easter_egg(void)
{
  printf("<<Arthur's Easter Egg>>\n");

  const char *keyword = arthur_egg.keyword;
  char binary[7][9]; /* 7 letters, 8 bits + '\0' */

  /* Convert each letter to 8-bit binary and reverse bits */
  for (int i = 0; i < 7; i++) {
    char_to_binary(keyword[i], binary[i]);
    reverse_str(binary[i]);
  }

  /* Print binary strings in reverse order */
  for (int i = 6; i >= 0; i--) {
    printf("%s\n", binary[i]);
  }

  char user_input[16];
  int correct_chars_entered = 0;

  /* Prompt user until correct characters entered */
  while (!correct_chars_entered) {
    printf("Enter the corresponding characters: ");
    read_line(user_input, sizeof(user_input));

    if (isRightChar(user_input, keyword)) {
      correct_chars_entered = 1;
    } else {
      printf("Incorrect input. Please try again.\n");
    }
  }

  printf("Combine the characters into a word: ");
  read_line(user_input, sizeof(user_input));

  if (isEasterEgg(user_input, &arthur_egg)) {
    printf("##Easter Egg Discovered!$$\n%s\n", arthur_egg.message);
  } else {
    printf("Wrong word. Returning to sub-menu.\n");
  }
}

/* Bonus: Shuffle keyword, convert to binary, reverse bits, rearrange */
static void shuffle_and_convert_keyword(const char *keyword)
{
  char letters[8];
  int len = (int)strlen(keyword);
  if (len > 7) len = 7;
  strncpy(letters, keyword, len);
  letters[len] = '\0';

  /* Shuffle with Fisher-Yates */
  srand((unsigned int)time(NULL));
  for (int i = len - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    char tmp = letters[i];
    letters[i] = letters[j];
    letters[j] = tmp;
  }

  /* Convert letters to reversed binary */
  char binaries[7][9];
  for (int i = 0; i < len; i++) {
    char_to_binary(letters[i], binaries[i]);
    reverse_str(binaries[i]);
  }

  printf("\nShuffled keyword: %s\n", letters);

  printf("Odd-indexed letters first (1,3,5...):\n");
  for (int i = 1; i < len; i += 2) {
    printf("%s\n", binaries[i]);
  }
  printf("Even-indexed letters next (0,2,4,6...):\n");
  for (int i = 0; i < len; i += 2) {
    printf("%s\n", binaries[i]);
  }
}

/* Menu and input system */

static void self_management_and_teamwork_menu(void)
{
  char input[64];

  while (1) {
    printf("\n[II. Training > 2. Self-Management and Teamwork]\n");
    printf("Enter name (or 'back' to return): ");
    read_line(input, sizeof(input));

    if (strcmp(input, "back") == 0) {
      break; /* return to previous menu */
    }

    if (strcmp(input, "Arthur") == 0) {
      find_easter_egg();
      /* After Easter egg, return to this sub-menu */
    } else {
      printf("Hello %s, keep training!\n", input);
    }
  }
}

static void training_menu(void)
{
  char input[16];

  while (1) {
    printf("\n[II. Training]\n");
    printf("1. Other Training Options (not implemented)\n");
    printf("2. Self-Management and Teamwork\n");
    printf("0. Back\n");
    printf("Select option: ");
    read_line(input, sizeof(input));

    if (strcmp(input, "0") == 0) {
      break; /* exit training menu */
    } else if (strcmp(input, "2") == 0) {
      self_management_and_teamwork_menu();
    } else {
      printf("Option not implemented or invalid. Try again.\n");
    }
  }
}

int main(void)
{
  char input[16];

  printf("Welcome to Millieways Training Program\n");

  while (1) {
    printf("\nMain Menu\n");
    printf("I. Other Options (not implemented)\n");
    printf("II. Training\n");
    printf("0. Exit\n");
    printf("Select option: ");
    read_line(input, sizeof(input));

    if (strcmp(input, "0") == 0) {
      printf("Goodbye!\n");
      break;
    } else if (strcmp(input, "II") == 0 || strcmp(input, "2") == 0) {
      training_menu();
    } else {
      printf("Invalid option. Please try again.\n");
    }
  }

  /* Uncomment to test bonus function independently */
  /* shuffle_and_convert_keyword(KEYWORD); */

  return 0;
}
