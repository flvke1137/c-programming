/*
 * stage2.c
 * Millieways Training Program - Self-Management, Teamwork, Trauma Management
 * ANSI C, gcc 9.x
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS    10
#define MAX_TRAUMA     10
#define MAX_QUESTIONS  5
#define MAX_RESPONSES  50

/*-------------------------------------------------------------------
 * MemberInfo from Assignment 1 (sample data)
 *-------------------------------------------------------------------*/
typedef struct {
    char nickname[30];
    int age;
    /* other fields as needed */
} MemberInfo;

MemberInfo milliewayMembers[MAX_MEMBERS] = {
    {"Ara", 22},
    {"Bora", 21},
    {"Chae", 23},
    {"Dami", 20},
    {"Eun", 22}
};
int memberCount = 5;

/*-------------------------------------------------------------------
 * Trauma Info Structs
 *-------------------------------------------------------------------*/
typedef struct {
    char nickname[30];
    int age;
    char traumaDesc[256];
    int hasTrauma;
} TraumaInfo;

typedef struct {
    int questionID;
    char questionContent[150];
} CounselingQuestion;

typedef struct {
    char nickname[30];
    int questionID;
    char response[101];
} CounselingResponse;

/*-------------------------------------------------------------------
 * Globals
 *-------------------------------------------------------------------*/
TraumaInfo traumaData[MAX_TRAUMA];
int traumaCount = 0;
CounselingResponse counselingResponses[MAX_RESPONSES];
int responseCount = 0;

/* Read-only counseling questions */
const CounselingQuestion counselingQuestions[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

/*-------------------------------------------------------------------
 * Function Prototypes
 *-------------------------------------------------------------------*/
int  findMemberIndexByNickname(const char *nickname);
int  findTraumaIndexByNickname(const char *nickname);
void inputTrauma(void);
void counselingSession(void);
void showCompletedCounseling(void);
void viewCounselingDetails(const char *nickname);
void overcomeTrauma(void);
void traumaMenu(void);
char getMenuChoice(void);
void selectThreeDistinctQuestions(int picks[3]);

/*-------------------------------------------------------------------
 * Implementation
 *-------------------------------------------------------------------*/

/* Find member in milliewayMembers */
int findMemberIndexByNickname(const char *nickname) {
    for (int i = 0; i < memberCount; i++) {
        if (strcasecmp(milliewayMembers[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

/* Find trauma entry */
int findTraumaIndexByNickname(const char *nickname) {
    for (int i = 0; i < traumaCount; i++) {
        if (strcasecmp(traumaData[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

/* Top-level overcomeTrauma called from main menu */
void overcomeTrauma(void) {
    traumaMenu();
}

/* Trauma management sub-menu */
void traumaMenu(void) {
    char choice;
    do {
        printf("\n== Trauma Management ==\n");
        printf("1. Input Trauma Data\n");
        printf("2. Counseling Session\n");
        printf("3. View Completed Counseling\n");
        printf("0. Return\n");
        printf("Select: ");
        choice = getMenuChoice();
        switch (choice) {
            case '1': inputTrauma(); break;
            case '2': counselingSession(); break;
            case '3': showCompletedCounseling(); break;
            case '0': printf("Returning...\n"); break;
            default:  printf("Invalid.\n");
        }
    } while (choice != '0');
}

/* Input trauma data for members */
void inputTrauma(void) {
    char nickname[30];
    char traumaDesc[256];
    char cont;
    do {
        printf("Enter nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = '\0';
        int midx = findMemberIndexByNickname(nickname);
        midx = (midx >= 0) ? midx : -1;  /* ternary operator use */
        if (midx == -1) {
            printf("Nickname not found.\n");
            continue;
        }
        int tidx = findTraumaIndexByNickname(nickname);
        if (tidx == -1) {
            if (traumaCount >= MAX_TRAUMA) {
                printf("Storage full.\n");
                return;
            }
            tidx = traumaCount++;
            strcpy(traumaData[tidx].nickname, nickname);
            traumaData[tidx].age = milliewayMembers[midx].age;
            traumaData[tidx].hasTrauma = 1;
        }
        printf("Enter trauma description: ");
        fgets(traumaDesc, sizeof(traumaDesc), stdin);
        traumaDesc[strcspn(traumaDesc, "\n")] = '\0';
        strncpy(traumaData[tidx].traumaDesc, traumaDesc, sizeof(traumaData[tidx].traumaDesc)-1);
        printf("Saved for %s.\n", nickname);
        printf("Add another? (Y/N): ");
        cont = getchar();
        while (getchar()!='\n');
    } while (cont=='Y' || cont=='y');
}

/* Counseling session for trauma entries */
void counselingSession(void) {
    if (traumaCount == 0) {
        printf("No trauma data.\n");
        return;
    }
    printf("Members with trauma:\n");
    for (int i = 0; i < traumaCount; i++) {
        printf("%d. %s\n", i+1, traumaData[i].nickname);
    }
    printf("Select (0 cancel): ");
    int sel;
    if (scanf("%d", &sel)!=1 || sel<0 || sel>traumaCount) {
        printf("Invalid.\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n');
    if (sel==0) return;
    char *nick = traumaData[sel-1].nickname;

    /* Track answered questions */
    int answered[MAX_QUESTIONS]={0};
    int countAns=0;
    for (int i=0; i<responseCount; i++) {
        if (strcasecmp(counselingResponses[i].nickname, nick)==0) {
            for (int j=0; j<MAX_QUESTIONS; j++) {
                if (counselingResponses[i].questionID == counselingQuestions[j].questionID) {
                    answered[j]=1;
                    countAns++;
                }
            }
        }
    }
    int picks[3]; selectThreeDistinctQuestions(picks);
    for (int i=0; i<3; i++) {
        int q = picks[i];
        if (answered[q]) continue;
        printf("Q%d: %s\n", counselingQuestions[q].questionID,
               counselingQuestions[q].questionContent);
        char resp[101];
        do {
            printf("Response (<=100 chars): ");
            fgets(resp, sizeof(resp), stdin);
            resp[strcspn(resp,"\n")]='\0';
            if (!*resp) printf("Cannot be empty.\n");
            else if (strlen(resp)>100) printf("Too long.\n");
            else break;
        } while(1);
        if (responseCount<MAX_RESPONSES) {
            strcpy(counselingResponses[responseCount].nickname, nick);
            counselingResponses[responseCount].questionID = counselingQuestions[q].questionID;
            strcpy(counselingResponses[responseCount].response, resp);
            responseCount++;
            answered[q]=1;
        }
    }
    printf("Session complete for %s.\n", nick);
}

/* List completed counseling and view details */
void showCompletedCounseling(void) {
    char listed[MAX_TRAUMA][30];
    int listedCnt=0;
    for (int i=0; i<responseCount; i++) {
        int found=0;
        for (int j=0; j<listedCnt; j++) {
            if (strcasecmp(listed[j], counselingResponses[i].nickname)==0) {
                found=1; break;
            }
        }
        if (!found) strcpy(listed[listedCnt++], counselingResponses[i].nickname);
    }
    if (!listedCnt) { printf("No sessions done.\n"); return; }
    printf("Completed:\n");
    for (int i=0; i<listedCnt; i++) printf("%d. %s\n", i+1, listed[i]);
    printf("Select (0 cancel): ");
    int sel; if(scanf("%d",&sel)!=1||sel<0||sel>listedCnt){printf("Invalid.\n");while(getchar()!='\n');return;} while(getchar()!='\n');
    if(sel) viewCounselingDetails(listed[sel-1]);
}

void viewCounselingDetails(const char *nickname) {
    int tidx = findTraumaIndexByNickname(nickname);
    if (tidx==-1) { printf("No trauma for %s.\n", nickname); return; }
    printf("\n--- %s ---\nTrauma: %s\n\nQ&A:\n", nickname, traumaData[tidx].traumaDesc);
    for (int i=0; i<responseCount; i++) {
        if (strcasecmp(counselingResponses[i].nickname, nickname)==0) {
            int qid = counselingResponses[i].questionID;
            for (int j=0; j<MAX_QUESTIONS; j++) {
                if (counselingQuestions[j].questionID == qid) {
                    printf("Q%d: %s\nA: %s\n\n", qid,
                           counselingQuestions[j].questionContent,
                           counselingResponses[i].response);
                }
            }
        }
    }
}

/* Get menu char */
char getMenuChoice(void) {
    char c = getchar();
    while (getchar()!='\n');
    return tolower(c);
}

/* Pick 3 distinct questions */
void selectThreeDistinctQuestions(int picks[3]) {
    int chosen[3] = {-1,-1,-1}, c=0, r;
    srand((unsigned)time(NULL));
    while(c<3) {
        r = rand()%MAX_QUESTIONS;
        int ok=1;
        for(int i=0;i<c;i++) if(chosen[i]==r) ok=0;
        if(ok) chosen[c++]=r;
    }
    for(int i=0;i<3;i++) picks[i]=chosen[i];
}

/*-------------------------------------------------------------------
 * Main and Menu Integration
 *-------------------------------------------------------------------*/
int main(void) {
    char choice;
    do {
        printf("\n=== Millieways Training ===\n");
        printf("1. Other Module...\n");
        printf("2. Self-Management & Teamwork\n");
        printf("0. Exit\n");
        printf("Select: ");
        choice = getMenuChoice();
        switch(choice) {
            case '1': /* stub */ break;
            case '2': overcomeTrauma(); break;
            case '0': printf("Goodbye!\n"); break;
            default:  printf("Invalid.\n");
        }
    } while(choice!='0');
    return 0;
}
