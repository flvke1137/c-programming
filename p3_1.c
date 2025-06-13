/* stage2.c
 * Millieway trainee mentoring matching system
 * ANSI C / GNU style
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 100
#define MAX_MENTORS 8
#define MAX_NAME_LEN 50

typedef struct {
  int id;                      /* mentor unique ID 1 to 8 */
  char name[MAX_NAME_LEN];
  int mentee_count;            /* number of mentees assigned */
} Mentor;

typedef struct {
  char nickname[MAX_NAME_LEN];
  int trainee_id;              /* sum of ASCII codes */
  int ability;                 /* random 100-1000 */
  int mentor_id;               /* assigned mentor ID (1 to 8), 0 if none */
} Trainee;

/* Converts nickname to int by summing ASCII values */
int parseIntMember(const char *nickname)
{
  int sum = 0;
  while (*nickname) {
    sum += (int)(*nickname);
    nickname++;
  }
  return sum;
}

/* Returns random ability value between 100 and 1000 */
int getRandomAbility(void)
{
  return (rand() % 901) + 100; /* 100 to 1000 */
}

/* Initialize trainees array from nickname list */
void initializeTrainees(const char trainee_names[][MAX_NAME_LEN], int count, Trainee trainees[])
{
  int i;
  for (i = 0; i < count; i++) {
    strncpy(trainees[i].nickname, trainee_names[i], MAX_NAME_LEN - 1);
    trainees[i].nickname[MAX_NAME_LEN - 1] = '\0';
    trainees[i].trainee_id = parseIntMember(trainees[i].nickname);
    trainees[i].ability = getRandomAbility();
    trainees[i].mentor_id = 0; /* not assigned yet */
  }
}

/* Input mentor info from user */
void inputMentors(Mentor mentors[], int *mentor_count)
{
  int count, i;
  printf("Enter number of mentors (1 to %d): ", MAX_MENTORS);
  scanf("%d", &count);
  if (count < 1)
    count = 1;
  else if (count > MAX_MENTORS)
    count = MAX_MENTORS;

  *mentor_count = count;

  for (i = 0; i < count; i++) {
    mentors[i].id = i + 1; /* assign IDs from 1 to count */
    printf("Enter name for mentor %d: ", mentors[i].id);
    scanf(" %49[^\n]", mentors[i].name);
    mentors[i].mentee_count = 0;
  }
}

/* Match trainees to mentors by (trainee_id % 8) + 1 == mentor_id
 * Bonus: assign only one mentee per mentor if possible */
void matchMentoring(Trainee trainees[], int trainee_count, Mentor mentors[], int mentor_count)
{
  int i;
  /* Clear mentee counts */
  for (i = 0; i < mentor_count; i++) {
    mentors[i].mentee_count = 0;
  }

  for (i = 0; i < trainee_count; i++) {
    int desired_mentor_id = (trainees[i].trainee_id % MAX_MENTORS) + 1;
    int j;
    /* Check if mentor_id exists and has no mentee assigned */
    for (j = 0; j < mentor_count; j++) {
      if (mentors[j].id == desired_mentor_id && mentors[j].mentee_count == 0) {
        trainees[i].mentor_id = desired_mentor_id;
        mentors[j].mentee_count = 1;
        break;
      }
    }
    if (j == mentor_count) {
      /* No available mentor with desired ID or already assigned, leave mentor_id = 0 */
      trainees[i].mentor_id = 0;
    }
  }
}

/* Print mentor assignments */
void printMentorAssignments(const Trainee trainees[], int trainee_count, const Mentor mentors[], int mentor_count)
{
  int i, j;
  printf("\nTrainee assignments:\n");
  printf("%-15s %-10s %-15s %-10s\n", "Nickname", "Trainee ID", "Mentor Name", "Mentor ID");
  printf("-----------------------------------------------------------\n");

  for (i = 0; i < trainee_count; i++) {
    if (trainees[i].mentor_id == 0) {
      printf("%-15s %-10d %-15s %-10s\n",
             trainees[i].nickname,
             trainees[i].trainee_id,
             "(None)",
             "-");
    } else {
      /* Find mentor name */
      for (j = 0; j < mentor_count; j++) {
        if (mentors[j].id == trainees[i].mentor_id) {
          printf("%-15s %-10d %-15s %-10d\n",
                 trainees[i].nickname,
                 trainees[i].trainee_id,
                 mentors[j].name,
                 mentors[j].id);
          break;
        }
      }
    }
  }
}

/* Sample menu implementation for demonstration */
void matchMentoringMenu(void)
{
  /* Example trainee nicknames (replace with your own or input) */
  const char trainee_names[][MAX_NAME_LEN] = {
    "alice",
    "bob",
    "charlie",
    "diana",
    "edward",
    "fiona",
    "george",
    "hannah",
    "ivan",
    "julia"
  };
  const int trainee_count = 10;

  Trainee trainees[MAX_TRAINEES];
  Mentor mentors[MAX_MENTORS];
  int mentor_count = 0;

  /* Seed random number generator */
  srand((unsigned int)time(NULL));

  initializeTrainees(trainee_names, trainee_count, trainees);
  inputMentors(mentors, &mentor_count);
  matchMentoring(trainees, trainee_count, mentors, mentor_count);
  printMentorAssignments(trainees, trainee_count, mentors, mentor_count);
}

int main(void)
{
  printf("Millieway Trainee Mentoring Matching\n");
  matchMentoringMenu();
  return 0;
}
