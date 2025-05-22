#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEMBERS 20
#define MAX_NAME_LENGTH 50
#define MAX_NICKNAME_LENGTH 20
#define FITNESS_TESTS 7

/* Structure to represent Milliways members */
struct MemberData {
    char name[MAX_NAME_LENGTH];
    char nickname[MAX_NICKNAME_LENGTH];
};

/* Global arrays */
struct MemberData milliways_members[MAX_MEMBERS];
float health_scores[MAX_MEMBERS][FITNESS_TESTS];
int num_members = 0;

/* Function prototypes */
void displayMainMenu(void);
void handleTrainingMenu(void);
void handlePhysicalTrainingMenu(void);
void setHealth(void);
void getHealth(void);
void parseHealthData(char *input, float *values, int size);
int findMemberByNickname(const char *nickname);

int main(void)
{
    /* Initialize member data */
    strcpy(milliways_members[0].name, "Arthur Dent");
    strcpy(milliways_members[0].nickname, "Arthur");
    
    strcpy(milliways_members[1].name, "Ford Prefect");
    strcpy(milliways_members[1].nickname, "Ford");
    
    strcpy(milliways_members[2].name, "Zaphod Beeblebrox");
    strcpy(milliways_members[2].nickname, "Zaphod");
    
    strcpy(milliways_members[3].name, "Trillian Astra");
    strcpy(milliways_members[3].nickname, "Trillian");
    
    strcpy(milliways_members[4].name, "Marvin");
    strcpy(milliways_members[4].nickname, "Android");
    
    num_members = 5;

    /* Initialize health_scores with default values (-1 indicates no data) */
    int i, j;
    for (i = 0; i < MAX_MEMBERS; i++) {
        for (j = 0; j < FITNESS_TESTS; j++) {
            health_scores[i][j] = -1.0;
        }
    }

    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); /* Consume newline character */
        
        switch (choice) {
            case 1:
                printf("\nI. Mission Planning selected\n");
                break;
            case 2:
                handleTrainingMenu();
                break;
            case 3:
                printf("\nIII. Resource Management selected\n");
                break;
            case 4:
                printf("\nIV. Communication selected\n");
                break;
            case 5:
                printf("\nV. Ship Systems selected\n");
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}

void displayMainMenu(void)
{
    printf("\n=== MAIN MENU ===\n");
    printf("1. Mission Planning\n");
    printf("2. Training\n");
    printf("3. Resource Management\n");
    printf("4. Communication\n");
    printf("5. Ship Systems\n");
    printf("6. Exit\n");
}

void handleTrainingMenu(void)
{
    int choice;
    
    do {
        printf("\n=== II. TRAINING MENU ===\n");
        printf("1. Physical Strength & Knowledge\n");
        printf("2. Mental Health\n");
        printf("3. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); /* Consume newline character */
        
        switch (choice) {
            case 1:
                handlePhysicalTrainingMenu();
                break;
            case 2:
                printf("\nMental Health Training selected\n");
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void handlePhysicalTrainingMenu(void)
{
    int choice;
    
    do {
        printf("\n=== PHYSICAL STRENGTH & KNOWLEDGE MENU ===\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("C. Return to Training Menu\n");
        printf("Enter your choice (A, B, or C): ");
        char option;
        scanf(" %c", &option);
        getchar(); /* Consume newline character */
        option = toupper(option);
        
        switch (option) {
            case 'A':
                setHealth();
                break;
            case 'B':
                getHealth();
                break;
            case 'C':
                printf("Returning to Training Menu...\n");
                choice = 3; /* Exit the loop */
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                choice = 0;
        }
    } while (choice != 3);
}

/* Function to parse comma-separated health data */
void parseHealthData(char *input, float *values, int size)
{
    char *token;
    int i = 0;
    
    token = strtok(input, ",");
    while (token != NULL && i < size) {
        values[i++] = atof(token);
        token = strtok(NULL, ",");
    }
    
    /* If fewer values were provided, fill the rest with -1 */
    while (i < size) {
        values[i++] = -1.0;
    }
}

/* Function to find a member by nickname */
int findMemberByNickname(const char *nickname)
{
    int i;
    for (i = 0; i < num_members; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1; /* Member not found */
}

/* Function to set health data for a member */
void setHealth(void)
{
    char nickname[MAX_NICKNAME_LENGTH];
    char input[200];
    float values[FITNESS_TESTS];
    
    printf("\n=== ENTER FITNESS DATA ===\n");
    
    /* Display available members */
    printf("Available Members:\n");
    int i;
    for (i = 0; i < num_members; i++) {
        printf("%d. %s (%s)\n", i+1, milliways_members[i].name, milliways_members[i].nickname);
    }
    
    printf("\nEnter member nickname: ");
    fgets(nickname, MAX_NICKNAME_LENGTH, stdin);
    nickname[strcspn(nickname, "\n")] = 0; /* Remove newline character */
    
    int member_index = findMemberByNickname(nickname);
    if (member_index == -1) {
        printf("Member with nickname '%s' not found.\n", nickname);
        return;
    }
    
    printf("\nEnter fitness test data as comma-separated values in the following order:\n");
    printf("1. 1-Mile Running Test (minutes)\n");
    printf("2. Speed Sprint (seconds for 100m)\n");
    printf("3. Push-ups (minutes to complete 30)\n");
    printf("4. Squats (minutes to complete 50)\n");
    printf("5. Arm Strength (minutes to complete 50 push-ups)\n");
    printf("6. Swimming (minutes for 400m)\n");
    printf("7. Weightlifting (bodyweight multiplier)\n");
    printf("\nExample: 7.5,12.3,1.2,2.5,3.7,8.2,1.5\n");
    printf("Enter data: ");
    
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; /* Remove newline character */
    
    parseHealthData(input, values, FITNESS_TESTS);
    
    /* Store the values in health_scores array */
    for (i = 0; i < FITNESS_TESTS; i++) {
        health_scores[member_index][i] = values[i];
    }
    
    printf("\nFitness data for %s has been updated successfully.\n", milliways_members[member_index].name);
}

/* Function to get and display health data */
void getHealth(void)
{
    char nickname[MAX_NICKNAME_LENGTH];
    int option, member_index, test_option;
    
    printf("\n=== VIEW FITNESS DATA ===\n");
    printf("1. View all members' fitness data\n");
    printf("2. View specific member's fitness data\n");
    printf("3. View specific test result for a member\n");
    printf("Enter option: ");
    scanf("%d", &option);
    getchar(); /* Consume newline character */
    
    switch (option) {
        case 1:
            /* Display all fitness data */
            printf("\n=== ALL FITNESS DATA ===\n");
            printf("%-20s %-15s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", 
                   "Name", "Nickname", "1-Mile", "Sprint", "Push-ups", "Squats", "Arm", "Swimming", "Weight");
            
            int i;
            for (i = 0; i < num_members; i++) {
                printf("%-20s %-15s ", milliways_members[i].name, milliways_members[i].nickname);
                
                int j;
                for (j = 0; j < FITNESS_TESTS; j++) {
                    if (health_scores[i][j] < 0) {
                        printf("%-10s ", "N/A");
                    } else {
                        printf("%-10.2f ", health_scores[i][j]);
                    }
                }
                printf("\n");
            }
            break;
            
        case 2:
            /* Get specific member's data */
            printf("\nEnter member nickname: ");
            fgets(nickname, MAX_NICKNAME_LENGTH, stdin);
            nickname[strcspn(nickname, "\n")] = 0; /* Remove newline character */
            
            member_index = findMemberByNickname(nickname);
            if (member_index == -1) {
                printf("Member with nickname '%s' not found.\n", nickname);
                return;
            }
            
            printf("\n=== FITNESS DATA FOR %s (%s) ===\n", 
                   milliways_members[member_index].name, 
                   milliways_members[member_index].nickname);
            
            printf("1. 1-Mile Running Test: ");
            health_scores[member_index][0] < 0 ? printf("N/A\n") : printf("%.2f minutes\n", health_scores[member_index][0]);
            
            printf("2. Speed Sprint (100m): ");
            health_scores[member_index][1] < 0 ? printf("N/A\n") : printf("%.2f seconds\n", health_scores[member_index][1]);
            
            printf("3. Push-ups (30): ");
            health_scores[member_index][2] < 0 ? printf("N/A\n") : printf("%.2f minutes\n", health_scores[member_index][2]);
            
            printf("4. Squats (50): ");
            health_scores[member_index][3] < 0 ? printf("N/A\n") : printf("%.2f minutes\n", health_scores[member_index][3]);
            
            printf("5. Arm Strength (50 push-ups): ");
            health_scores[member_index][4] < 0 ? printf("N/A\n") : printf("%.2f minutes\n", health_scores[member_index][4]);
            
            printf("6. Swimming (400m): ");
            health_scores[member_index][5] < 0 ? printf("N/A\n") : printf("%.2f minutes\n", health_scores[member_index][5]);
            
            printf("7. Weightlifting (Bench Press): ");
            health_scores[member_index][6] < 0 ? printf("N/A\n") : printf("%.2f x bodyweight\n", health_scores[member_index][6]);
            
            break;
            
        case 3:
            /* Get specific test result for a member */
            printf("\nEnter member nickname: ");
            fgets(nickname, MAX_NICKNAME_LENGTH, stdin);
            nickname[strcspn(nickname, "\n")] = 0; /* Remove newline character */
            
            member_index = findMemberByNickname(nickname);
            if (member_index == -1) {
                printf("Member with nickname '%s' not found.\n", nickname);
                return;
            }
            
            printf("\nSelect fitness test (1-7):\n");
            printf("1. 1-Mile Running Test\n");
            printf("2. Speed Sprint\n");
            printf("3. Push-ups (30)\n");
            printf("4. Squats (50)\n");
            printf("5. Arm Strength (50 push-ups)\n");
            printf("6. Swimming (400m)\n");
            printf("7. Weightlifting (Bench Press)\n");
            printf("Enter test number: ");
            scanf("%d", &test_option);
            getchar(); /* Consume newline character */
            
            if (test_option < 1 || test_option > FITNESS_TESTS) {
                printf("Invalid test number.\n");
                return;
            }
            
            test_option--; /* Adjust for zero-based index */
            
            const char *test_names[] = {
                "1-Mile Running Test",
                "Speed Sprint (100m)",
                "Push-ups (30)",
                "Squats (50)",
                "Arm Strength (50 push-ups)",
                "Swimming (400m)",
                "Weightlifting (Bench Press)"
            };
            
            const char *units[] = {
                "minutes",
                "seconds",
                "minutes",
                "minutes",
                "minutes",
                "minutes",
                "x bodyweight"
            };
            
            printf("\n%s (%s) - %s: ", 
                   milliways_members[member_index].name, 
                   milliways_members[member_index].nickname,
                   test_names[test_option]);
            
            if (health_scores[member_index][test_option] < 0) {
                printf("N/A\n");
            } else {
                printf("%.2f %s\n", health_scores[member_index][test_option], units[test_option]);
            }
            
            break;
            
        default:
            printf("Invalid option.\n");
    }
}