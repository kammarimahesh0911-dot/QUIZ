/* 
   Compile: gcc quiz_app.c -o quiz_app
   Run: ./quiz_app                                       */

#include <stdio.h>

//#define tells the compiler to replace a name with the assigned value (or) it gives a name to a fixed value.
#define TOTAL 5
#define SCORE_FILE "scores.txt" //"score.txt" is the name of the strings ka file where the scores will be saved.



//User-defined data type to store all the variables, "QUESTION" is name of the data type which holds the relevant variables in it.
// For data type "struct" is used. Full form of struct is "structure". Structure is a user-defined data type in C which allows to combine data items/variables of different kinds.
struct Question {
    char text[100]; //Text limit of 100 characters for each question
    char options[4][40]; //Options limit of 4 options with 40 characters for each option
    char correct;
};


//Array structure to hold all the questions and their options
struct Question quiz[TOTAL] = {
//"quiz" is an array of user defined datatype "Question" which holds the questions and their options. Each question is stored as a structure with its text, options, and correct answer.

    // {"Question", {"option1", "option2", "option3", "option4"}, 'correct_option'},-----We shall use this format to frame the questions.
    // After we finalize what questions to be added.

};

int getChoice(void)                       /* read a menu number safely */
{
    int choice;
    int result = scanf("%d", &choice);
    if (result == EOF)
        return 3;                         /* input ended: exit */
    clearLine();
    return (result == 1) ? choice : 0;    /* 0 = invalid */
}

char getAnswer(void)                      /* keep asking until A, B, C or D */
{
    char c, next;
    while (1) {
        printf("  Your answer (A-D): ");
        if (scanf(" %c", &c) != 1)
            return '\0';                 /* input ended */
        next = getchar();
        if (c >= 'a' && c <= 'z')
            c = c - 32;                   /* lower case -> upper case */
        if (next == '\n' && c >= 'A' && c <= 'D')
            return c;
        while (next != '\n' && next != EOF)
            next = getchar();
        printf("  Invalid input. Please enter A, B, C or D.\n");
    }
}

void saveScore(const char *name, int score)
{
    FILE *fp = fopen(SCORE_FILE, "a");
    if (fp == NULL) {
        printf("  Could not save the score.\n");
        return;
    }
    fprintf(fp, "%-20s %d / %d\n", name, score, TOTAL);
    fclose(fp);
}

void playQuiz(void)
{
    char name[30];
    int score = 0;

    printf("\n  Enter your name: ");
    if (scanf("%29s", name) != 1)
        return;
    clearLine();

    for (int i = 0; i < TOTAL; i++) {
        printf("\n  ------------------------------------------\n");
        printf("  Question %d of %d\n", i + 1, TOTAL);
        printf("  %s\n\n", quiz[i].text);
        for (int j = 0; j < 4; j++)
            printf("     %c) %s\n", 'A' + j, quiz[i].options[j]);
        printf("\n");

        char answer = getAnswer();
        if (answer == '\0')
            return;                       /* input ended */
        if (answer == quiz[i].correct) {
            printf("  [+] Correct!\n");
            score++;
        } else {
            printf("  [x] Wrong. The answer is %c.\n", quiz[i].correct);
        }
    }

    printf("\n  ==========================================\n");
    printf("   RESULT: %s\n", name);
    printf("   Score : %d / %d  (%d%%)\n", score, TOTAL, score * 100 / TOTAL);
    printf("  ==========================================\n");
    saveScore(name, score);
}

void showScores(void)
{
    char line[100];
    FILE *fp = fopen(SCORE_FILE, "r");

    printf("\n  ============= HIGH SCORES ================\n");
    if (fp == NULL) {
        printf("   No scores recorded yet.\n");
    } else {
        while (fgets(line, sizeof line, fp) != NULL)
            printf("   %s", line);
        fclose(fp);
    }
    printf("  ==========================================\n");
}

int main(void)
{
    int choice;
    do {
        printf("\n  ==========================================\n");
        printf("             C QUIZ APPLICATION\n");
        printf("  ==========================================\n");
        printf("     1. Start Quiz\n");
        printf("     2. View Scores\n");
        printf("     3. Exit\n");
        printf("  ------------------------------------------\n");
        printf("  Enter choice (1-3): ");

        choice = getChoice();
        if (choice == 1)
            playQuiz();
        else if (choice == 2)
            showScores();
        else if (choice == 3)
            printf("\n  Goodbye!\n\n");
        else
            printf("\n  Invalid choice. Please enter 1, 2 or 3.\n");
    } while (choice != 3);

    return 0;
}
