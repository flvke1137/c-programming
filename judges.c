#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_STRING_LEN 1024
#define MAX_FIELD_LEN 100

// Array to store judge information in JSON format
char judges_array[MAX_JUDGES][MAX_STRING_LEN];

// Function prototypes
void display_header(const char *title);
void get_judge_info(int judge_number, char *output);
void parse_and_display_judge(int judge_number, const char *info);
void clear_input_buffer();

int main() {
    char project_name[100];
    int total_judges = 0;
    int selected_members = 0;
    char check_option;

    // Display header
    display_header("Judge List Data Entry");

    // Get project information
    printf("\nParticipating Project: ");
    scanf("%99s", project_name);
    clear_input_buffer();

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    clear_input_buffer();

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    clear_input_buffer();

    // Validate inputs
    if (total_judges <= 0 || total_judges > MAX_JUDGES) {
        printf("Invalid number of judges. Please enter a number between 1 and %d.\n", MAX_JUDGES);
        return 1;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    // Input judge information one by one
    for (int i = 0; i < total_judges; i++) {
        printf("\n--- Judge %d Information ---\n", i + 1);
        get_judge_info(i + 1, judges_array[i]);
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    // Ask to check judge information
    printf("%s: Should we check the judge information? ", project_name);
    scanf(" %c", &check_option);

    if (check_option == 'Y' || check_option == 'y') {
        display_header("Display Judge Data");

        // Display each judge's information
        for (int i = 0; i < total_judges; i++) {
            parse_and_display_judge(i + 1, judges_array[i]);
            
            if (i < total_judges - 1) {
                printf("-----------------------------------\n");
            }
        }
    }

    return 0;
}

void display_header(const char *title) {
    printf("\n####################################\n");
    printf("#%*s%s%*s#\n", 
           (36 - strlen(title)) / 2, "", 
           title, 
           (36 - strlen(title) - (36 - strlen(title)) / 2), "");
    printf("####################################\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void get_judge_info(int judge_number, char *output) {
    char name[MAX_FIELD_LEN] = "";
    char gender[MAX_FIELD_LEN] = "";
    char affiliation[MAX_FIELD_LEN] = "";
    char title[MAX_FIELD_LEN] = "";
    char expertise[MAX_FIELD_LEN] = "";
    char email[MAX_FIELD_LEN] = "";
    char phone[MAX_FIELD_LEN] = "";
    
    // Get individual fields
    printf("Name: ");
    fgets(name, MAX_FIELD_LEN, stdin);
    name[strcspn(name, "\n")] = 0;  // Remove newline
    
    printf("Gender: ");
    fgets(gender, MAX_FIELD_LEN, stdin);
    gender[strcspn(gender, "\n")] = 0;
    
    printf("Affiliation: ");
    fgets(affiliation, MAX_FIELD_LEN, stdin);
    affiliation[strcspn(affiliation, "\n")] = 0;
    
    printf("Title: ");
    fgets(title, MAX_FIELD_LEN, stdin);
    title[strcspn(title, "\n")] = 0;
    
    printf("Expertise: ");
    fgets(expertise, MAX_FIELD_LEN, stdin);
    expertise[strcspn(expertise, "\n")] = 0;
    
    printf("Email: ");
    fgets(email, MAX_FIELD_LEN, stdin);
    email[strcspn(email, "\n")] = 0;
    
    printf("Phone: ");
    fgets(phone, MAX_FIELD_LEN, stdin);
    phone[strcspn(phone, "\n")] = 0;
    
    // Format the data into the required string format
    sprintf(output, "Name: %s, Gender: %s, Affiliation: %s, Title: %s, Specialty: %s, Email: %s, Phone: %s",
            name, gender, affiliation, title, expertise, email, phone);
    
    printf("Judge %d information has been recorded.\n", judge_number);
}

void parse_and_display_judge(int judge_number, const char *info) {
    char name[MAX_FIELD_LEN] = "";
    char gender[MAX_FIELD_LEN] = "";
    char affiliation[MAX_FIELD_LEN] = "";
    char title[MAX_FIELD_LEN] = "";
    char expertise[MAX_FIELD_LEN] = "";
    char email[MAX_FIELD_LEN] = "";
    char phone[MAX_FIELD_LEN] = "";

    char field_name[50];
    char field_value[MAX_FIELD_LEN];
    int i = 0, j = 0;

    printf("[Judge %d]\n", judge_number);

    // Parse the judge information string
    while (info[i] != '\0') {
        // Skip spaces
        while (info[i] == ' ') i++;

        // Extract field name
        j = 0;
        while (info[i] != ':' && info[i] != '\0') {
            field_name[j++] = info[i++];
        }
        field_name[j] = '\0';
        
        // Skip the colon and spaces
        if (info[i] == ':') i++;
        while (info[i] == ' ') i++;

        // Extract field value
        j = 0;
        while (info[i] != ',' && info[i] != '\0') {
            field_value[j++] = info[i++];
        }
        field_value[j] = '\0';
        
        // Remove trailing spaces from field value
        while (j > 0 && field_value[j-1] == ' ') field_value[--j] = '\0';

        // Assign value to appropriate field
        if (strstr(field_name, "Name") != NULL) {
            strcpy(name, field_value);
        } else if (strstr(field_name, "Gender") != NULL) {
            strcpy(gender, field_value);
        } else if (strstr(field_name, "Affiliation") != NULL) {
            strcpy(affiliation, field_value);
        } else if (strstr(field_name, "Title") != NULL) {
            strcpy(title, field_value);
        } else if (strstr(field_name, "Specialty") != NULL || strstr(field_name, "Expertise") != NULL) {
            strcpy(expertise, field_value);
        } else if (strstr(field_name, "Email") != NULL) {
            strcpy(email, field_value);
        } else if (strstr(field_name, "Phone") != NULL) {
            strcpy(phone, field_value);
        }

        // Skip the comma
        if (info[i] == ',') i++;
    }

    // Display the parsed information
    printf("Name: %s\n", name);
    printf("Gender: %s\n", gender);
    printf("Affiliation: %s\n", affiliation);
    printf("Title: %s\n", title);
    printf("Expertise: %s\n", expertise);
    printf("Email: %s\n", email);
    printf("Phone: %s\n", phone);
}