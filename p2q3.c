#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10

/* Mocked milliways_members from Problem 2 */
typedef struct {
    char name[50];
    char nickname[50];
} Member;

Member milliways_members[MAX_MEMBERS] = {
    {"Alice", "Ace"},
    {"Bob", "Bobby"},
    {"Charlie", "Chuck"}
};
int num_members = 3;

/* Exercise types by category */
const char* exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},          // Cardio
    {"Push-ups", "Squats", NULL},                    // Full-body Strength
    {"Leg Press", "Leg Curl", NULL},                 // Lower-body Strength
    {"Pull-ups", "Chin-ups", NULL},                  // Upper-body Strength
    {"Plank", "Crunches", NULL}                      // Core Strength
};

/* Member workout routine struct */
typedef struct {
    char* routine[6][2];  /* 6 days (Mon-Sat), each day 2 exercises [0]=cardio, [1]=strength/core */
} MemberRoutine;

MemberRoutine member_routines[MAX_MEMBERS];

/* Display the list of members */
void displayMemberList() {
    printf("\nMilliways Member List:\n");
    for (int i = 0; i < num_members; i++) {
        printf(" - %s (%s)\n", milliways_members[i].name, milliways_members[i].nickname);
    }
    printf("\n");
}

/* Set exercise routine for a member */
void setExerciseRoutine() {
    char name[50];
    int member_index = -1;

    printf("Enter member's name to set routine: ");
    scanf("%49s", name);

    /* Find member */
    for (int i = 0; i < num_members; i++) {
        if (strcmp(name, milliways_members[i].name) == 0) {
            member_index = i;
            break;
        }
    }
    if (member_index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Setting workout routine for %s (%s)\n", milliways_members[member_index].name, milliways_members[member_index].nickname);

    int core_used = 0;
    for (int day = 0; day < 6; day++) {
        printf("\nDay %d (%s)\n", day + 1,
            (day == 0) ? "Monday" :
            (day == 1) ? "Tuesday" :
            (day == 2) ? "Wednesday" :
            (day == 3) ? "Thursday" :
            (day == 4) ? "Friday" : "Saturday");

        /* Cardio selection */
        printf("Select a cardio exercise:\n");
        for (int i = 0; i < 3; i++) {
            printf(" %d. %s\n", i, exercise_types[0][i]);
        }
        int cardio_choice;
        printf("Choice (0-2): ");
        scanf("%d", &cardio_choice);
        if (cardio_choice < 0 || cardio_choice > 2) {
            printf("Invalid cardio choice, try again.\n");
            day--;
            continue;
        }
        member_routines[member_index].routine[day][0] = (char*)exercise_types[0][cardio_choice];

        /* Strength or core selection */
        printf("Select exercise type:\n");
        printf(" 1. Full-body Strength\n 2. Lower-body Strength\n 3. Upper-body Strength\n 4. Core Strength\n");
        int type_choice;
        printf("Choice (1-4): ");
        scanf("%d", &type_choice);

        if (type_choice < 1 || type_choice > 4) {
            printf("Invalid type choice, try again.\n");
            day--;
            continue;
        }

        /* Core exercise can only be used once per week */
        if (type_choice == 4 && core_used) {
            printf("Core exercise already used this week. Please choose a different type.\n");
            day--;
            continue;
        }
        if (type_choice == 4) {
            core_used = 1;
        }

        /* List exercises for the chosen type */
        int max_ex = 0;
        while (exercise_types[type_choice][max_ex] != NULL) max_ex++;
        printf("Select an exercise:\n");
        for (int i = 0; i < max_ex; i++) {
            printf(" %d. %s\n", i, exercise_types[type_choice][i]);
        }
        int ex_choice;
        printf("Choice (0-%d): ", max_ex - 1);
        scanf("%d", &ex_choice);
        if (ex_choice < 0 || ex_choice >= max_ex) {
            printf("Invalid exercise choice, try again.\n");
            day--;
            continue;
        }
        member_routines[member_index].routine[day][1] = (char*)exercise_types[type_choice][ex_choice];
    }

    printf("\nWorkout routine set successfully for %s!\n\n", milliways_members[member_index].name);
}

/* Display workout routine for a member */
void getExerciseRoutine() {
    char name[50];
    int member_index = -1;

    printf("Enter member's name to view routine: ");
    scanf("%49s", name);

    /* Find member */
    for (int i = 0; i < num_members; i++) {
        if (strcmp(name, milliways_members[i].name) == 0) {
            member_index = i;
            break;
        }
    }
    if (member_index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\nWorkout Routine for %s (%s):\n", milliways_members[member_index].name, milliways_members[member_index].nickname);

    const char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for (int i = 0; i < 6; i++) {
        printf("%s: Cardio - %s | Strength/Core - %s\n",
            days[i],
            member_routines[member_index].routine[i][0] ? member_routines[member_index].routine[i][0] : "Not set",
            member_routines[member_index].routine[i][1] ? member_routines[member_index].routine[i][1] : "Not set");
    }
    printf("\n");
}

/* Main menu */
void menu() {
    char choice;
    while (1) {
        printf("=== Milliways Training Menu ===\n");
        printf("C. Set Basic Workout Routine\n");
        printf("D. View Basic Workout Routine\n");
        printf("Q. Quit\n");
        printf("Select an option: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'C':
            case 'c':
                displayMemberList();
                setExerciseRoutine();
                break;
            case 'D':
            case 'd':
                displayMemberList();
                getExerciseRoutine();
                break;
            case 'Q':
            case 'q':
                printf("Exiting program.\n");
                return;
            default:
                printf("Invalid option, try again.\n");
        }
    }
}

int main() {
    /* Initialize all routines to NULL */
    for (int i = 0; i < num_members; i++) {
        for (int d = 0; d < 6; d++) {
            member_routines[i].routine[d][0] = NULL;
            member_routines[i].routine[d][1] = NULL;
        }
    }

    menu();

    return 0;
}
