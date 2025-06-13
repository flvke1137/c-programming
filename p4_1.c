#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // For sleep()

#define MAX_QUESTIONS 10
#define QUIZ_QUESTIONS 5
#define MAX_TRAINEES 4

typedef struct {
    int id;
    char question[256];
    char answer[128];
} KoreanQuestion;

typedef struct {
    char name[50];
    char nickname[50];
    char nationality[50];
    int score;
    char pass; // 'Y' or 'N'
} Trainee;

typedef struct {
    int questionId;
    char correctness; // 'O' or 'X'
} QuizAnswer;

/* Question bank */
KoreanQuestion questionBank[MAX_QUESTIONS] = {
    {1, "What is 'Hello' in Korean?", "안녕하세요"},
    {2, "What is 'Thank you' in Korean?", "감사합니다"},
    {3, "What is 'Yes' in Korean?", "네"},
    {4, "What is 'No' in Korean?", "아니요"},
    {5, "What is 'I love you' in Korean?", "사랑해요"},
    {6, "What is 'Goodbye' (formal) in Korean?", "안녕히 가세요"},
    {7, "What is 'Excuse me' in Korean?", "실례합니다"},
    {8, "What is 'I'm sorry' in Korean?", "죄송합니다"},
    {9, "What is 'Please' in Korean?", "부탁합니다"},
    {10, "What is 'My name is...' in Korean?", "제 이름은 ...입니다"}
};

/* Trainee data */
Trainee trainees[MAX_TRAINEES] = {
    {"Park Ji-yeon", "Jiyeon", "Korea", 0, 'N'},
    {"Arthur Dent", "Arthur", "UK", 0, 'N'},
    {"Ford Prefect", "Ford", "Betelgeuse", 0, 'N'},
    {"Zaphod Beeblebrox", "Zaphod", "Galactic", 0, 'N'}
};

/* Select a random non-Korean trainee */
int
selectRandomTaker(void)
{
    int index;
    srand((unsigned int) time(NULL));
    do {
        index = rand() % MAX_TRAINEES;
    } while (strcmp(trainees[index].nationality, "Korea") == 0);

    printf("Welcome, %s, to the Korean quiz session!\n", trainees[index].name);
    return index;
}

/* Run the quiz session for a trainee */
void
serveRandomQuiz(int traineeIndex)
{
    int used[MAX_QUESTIONS] = {0};
    QuizAnswer answers[QUIZ_QUESTIONS];
    int selected, totalScore = 0;
    char userAnswer[128];
    int i;

    printf("The quiz will begin in 30 seconds. Prepare yourself...\n");
    sleep(30);

    for (i = 0; i < QUIZ_QUESTIONS; ++i) {
        do {
            selected = rand() % MAX_QUESTIONS;
        } while (used[selected]);
        used[selected] = 1;

        KoreanQuestion q = questionBank[selected];

        printf("Q%d: %s\nYour answer: ", i + 1, q.question);
        scanf(" %[^\n]", userAnswer);

        answers[i].questionId = q.id;
        answers[i].correctness = (strcmp(userAnswer, q.answer) == 0) ? 'O' : 'X';
        if (answers[i].correctness == 'O') {
            totalScore += 20;
        }
    }

    trainees[traineeIndex].score = totalScore;
    trainees[traineeIndex].pass = (totalScore >= 80) ? 'Y' : 'N';

    printf("\n--- Answer Sheet ---\n");
    for (i = 0; i < QUIZ_QUESTIONS; ++i) {
        printf("Q%d (ID: %d): %c\n",
               i + 1, answers[i].questionId, answers[i].correctness);
    }

    printf("Total Score: %d\n", totalScore);
    printf("Pass Status: %c\n", trainees[traineeIndex].pass);
}

/* Main test function entry */
void
testKoreanLang(void)
{
    int traineeIndex = selectRandomTaker();
    serveRandomQuiz(traineeIndex);
}

/* Optional simple menu for integration */
int
main(void)
{
    int choice;

    while (1) {
        printf("\n[II. Training > 3. Language and Pronunciation Training > A. Korean Quiz]\n");
        printf("1. Take Korean Quiz\n");
        printf("0. Exit\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                testKoreanLang();
                break;
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid selection.\n");
        }
    }

    return 0;
}
