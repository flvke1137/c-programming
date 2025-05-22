#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STAGES 8

// Training stage status: 'N' = not attempted, 'P' = passed, 'F' = failed
char trainingStatus[MAX_STAGES] = {'N','N','N','N','N','N','N','N'};

const char *mainMenu[3] = {
    "1. Audition Management",
    "2. Training",
    "3. Debut"
};

const char *trainingMenu[8] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Utility function to check if stage is passed
int isStagePassed(int stageIndex) {
    return trainingStatus[stageIndex] == 'P';
}

// Show main menu
void showMainMenu() {
    printf("\n--- Main Menu ---\n");
    for (int i = 0; i < 3; i++) {
        printf("%s\n", mainMenu[i]);
    }
    printf("Enter your choice (or 0/Q/q to quit): ");
}

// Show training menu
void showTrainingMenu() {
    printf("\n--- Training Menu ---\n");
    for (int i = 0; i < MAX_STAGES; i++) {
        printf("%s [%c]\n", trainingMenu[i], trainingStatus[i]);
    }
    printf("Select a stage to train (1-8) or 0 to go back: ");
}

// Function to handle training stage logic
void handleTraining() {
    int stage;
    char input[10];

    while (1) {
        showTrainingMenu();
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0') break;

        stage = atoi(input);
        if (stage < 1 || stage > 8) {
            printf("Invalid stage. Try again.\n");
            continue;
        }

        // Stage 1 & 2 must be completed in order
        if (stage == 2 && !isStagePassed(0)) {
            printf("You must complete Stage 1 before Stage 2.\n");
            continue;
        }

        if (stage >= 3 && (!isStagePassed(0) || !isStagePassed(1))) {
            printf("You must complete Stage 1 and 2 before Stage 3-8.\n");
            continue;
        }

        if (isStagePassed(stage - 1)) {
            printf("You already passed this stage. Cannot re-select.\n");
            continue;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (toupper(input[0]) != 'Y') continue;

        printf("Did you complete the training and pass the certification? (P/F): ");
        fgets(input, sizeof(input), stdin);
        char result = toupper(input[0]);

        if (result == 'P' || result == 'F') {
            trainingStatus[stage - 1] = result;
            printf("Training result for stage %d recorded as [%c]\n", stage, result);
        } else {
            printf("Invalid input. Returning to training menu.\n");
        }
    }
}

// Main program loop
int main() {
    char input[10];

    printf("Welcome to Magrathea Training System\n");

    while (1) {
        showMainMenu();
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || toupper(input[0]) == 'Q') {
            printf("Exiting the program. Goodbye!\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf("Audition Management selected. (Functionality not implemented)\n");
                break;
            case '2':
                handleTraining();
                break;
            case '3':
                printf("Debut selected. (Functionality not implemented)\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}
