#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define INFO_SIZE 11
#define MAX_STRING_SIZE 100

int main(void) {
    char candidate01[INFO_SIZE][MAX_STRING_SIZE];
    char candidate02[INFO_SIZE][MAX_STRING_SIZE];
    char candidate03[INFO_SIZE][MAX_STRING_SIZE];
    char candidate04[INFO_SIZE][MAX_STRING_SIZE];
    char candidate05[INFO_SIZE][MAX_STRING_SIZE];
    char candidate06[INFO_SIZE][MAX_STRING_SIZE];
    
    char *member_info[INFO_SIZE] = {
        "Name",
        "Date of Birth (YYYY/MM/DD format)",
        "Gender (F for Female, M for Male)",
        "Email",
        "Nationality",
        "BMI",
        "Primary Skill",
        "Secondary Skill",
        "Korean Proficiency Level (TOPIK)",
        "MBTI",
        "Introduction"
    };
    
    char audition_name[MAX_STRING_SIZE] = "";
    int i, c;
    
    // Get audition group name (bonus feature)
    printf("Enter audition group name: ");
    i = 0;
    while ((c = getchar()) != '\n' && i < MAX_STRING_SIZE - 1) {
        audition_name[i++] = (char)c;
    }
    audition_name[i] = '\0';
    
    // Input data for each candidate
    char (*candidates[NUM_CANDIDATES])[MAX_STRING_SIZE] = {
        candidate01, candidate02, candidate03, 
        candidate04, candidate05, candidate06
    };
    
    printf("\n####################################\n");
    if (audition_name[0] != '\0') {
        printf("[%s] Audition Candidate Data Entry\n", audition_name);
    } else {
        printf("Audition Candidate Data Entry\n");
    }
    printf("####################################\n");
    
    int candidate_idx = 0;
    while (candidate_idx < NUM_CANDIDATES) {
        printf("\nEntering information for the %s candidate.\n", 
               candidate_idx == 0 ? "first" : 
               candidate_idx == 1 ? "second" : 
               candidate_idx == 2 ? "third" : 
               candidate_idx == 3 ? "fourth" : 
               candidate_idx == 4 ? "fifth" : "sixth");
        printf("---------------------------------\n");
        
        for (i = 0; i < INFO_SIZE; i++) {
            printf("%d. %s: ", i + 1, member_info[i]);
            
            if (fgets(candidates[candidate_idx][i], MAX_STRING_SIZE, stdin) != NULL) {
                // Remove newline character if present
                int len = 0;
                while (candidates[candidate_idx][i][len] != '\0' && 
                       candidates[candidate_idx][i][len] != '\n') {
                    len++;
                }
                candidates[candidate_idx][i][len] = '\0';
            }
        }
        
        printf("=================================\n");
        candidate_idx++;
    }
    
    // Display candidate information
    printf("\n####################################\n");
    if (audition_name[0] != '\0') {
        printf("[%s] Audition Candidate Data Review\n", audition_name);
    } else {
        printf("Audition Candidate Data Review\n");
    }
    printf("####################################\n");
    
    printf("=============================================================================================\n");
    printf("%-13s | %-10s | %-6s | %-21s | %-11s | %-4s | %-13s | %-15s | %-5s | %-4s |\n", 
           "Name", "DOB", "Gender", "Email", "Nationality", "BMI", 
           "Primary Skill", "Secondary Skill", "TOPIK", "MBTI");
    printf("=============================================================================================\n");
    
    for (candidate_idx = 0; candidate_idx < NUM_CANDIDATES; candidate_idx++) {
        // Calculate age (bonus feature)
        int birth_year = 0, birth_month = 0, birth_day = 0;
        int current_year = 2025, current_month = 4, current_day = 15; // Current date from the task
        char dob_copy[MAX_STRING_SIZE];
        int age = 0;
        
        // Copy DOB to avoid modifying the original
        strcpy(dob_copy, candidates[candidate_idx][1]);
        
        // Parse DOB manually without strtok
        if (strlen(dob_copy) >= 10) { // Format should be YYYY/MM/DD
            char year_str[5] = {dob_copy[0], dob_copy[1], dob_copy[2], dob_copy[3], '\0'};
            char month_str[3] = {dob_copy[5], dob_copy[6], '\0'};
            char day_str[3] = {dob_copy[8], dob_copy[9], '\0'};
            
            birth_year = atoi(year_str);
            birth_month = atoi(month_str);
            birth_day = atoi(day_str);
        }
        
        // Calculate age
        age = current_year - birth_year;
        if (current_month < birth_month || 
            (current_month == birth_month && current_day < birth_day)) {
            age--;
        }
        
        // Format DOB for display (YYYYMMDD)
        char formatted_dob[9];
        sprintf(formatted_dob, "%04d%02d%02d", birth_year, birth_month, birth_day);
        
        // Display candidate information
        printf("%-13s (%d) | %-10s | %-6s | %-21s | %-11s | %-4s | %-13s | %-15s | %-5s | %-4s |\n", 
               candidates[candidate_idx][0], age, 
               formatted_dob, 
               candidates[candidate_idx][2], 
               candidates[candidate_idx][3], 
               candidates[candidate_idx][4], 
               candidates[candidate_idx][5], 
               candidates[candidate_idx][6], 
               candidates[candidate_idx][7], 
               candidates[candidate_idx][8], 
               candidates[candidate_idx][9]);
        
        printf("-------------------------------------------------------------------------------------\n");
        printf("%-83s|\n", candidates[candidate_idx][10]);
        printf("---------------------------------------------------------------------------------------------\n");
    }
    
    return 0;
}