#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For sleep function

// Function to simulate clearing the screen
void clear_screen() {
    for (int i = 0; i < 1; i++) {
        printf("\n");
    }
}

// Function to display the splash screen
void display_splash_screen(char *name, char *date) {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("                                        [Magrathea ver 0.1]                               \n");
    printf("                   Magrathea, where a shining planet is created in a wasteland with no grass,         \n");
    printf("           a place where unseen potential is discovered and gems are polished by the hands of experts,    \n");
    printf("                                        Welcome to Magrathea.   \n");
    printf("                                                                                                              \n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("=============================================================================================================\n");
}

int main() {
    char date[11]; // To store the date in 'yyyy-mm-dd' format
    char name[100]; // To store the name of the user

    // Get user input
    printf("Please enter the current date in the 'yyyy-mm-dd' format: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0'; // Remove the newline character

    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove the newline character

    // Confirm input has been processed
    printf("\n**The input has been processed successfully.**\n");

    // Wait for 3 seconds before clearing the screen
    sleep(3);

    // Clear the screen
    clear_screen();

    // Display the splash screen with the entered name and date
    display_splash_screen(name, date);

    return 0;
}
