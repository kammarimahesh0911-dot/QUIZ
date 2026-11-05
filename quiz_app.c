/* 
   Compile: gcc quiz_app.c -o quiz_app
   Run: ./quiz_app   (PowerShell: .\quiz_app)               */
 
//"stdio.h" stands for standard input output. It gives us the functions for printing, reading input and working with files (printf, scanf, getchar, fopen, fprintf, fgets, fclose).
#include <stdio.h>
 
//#define tells the compiler to replace a name with the assigned value (or) it gives a name to a fixed value.
#define TOTAL 5 //TOTAL is the number of questions in the quiz. Change it here once and the whole program updates.
#define SCORE_FILE "scores.txt" //"scores.txt" is the name of the file where the scores will be saved.
 
 
 
//User-defined data type to store all the variables, "QUESTION" is name of the data type which holds the relevant variables in it.
// For data type "struct" is used. Full form of struct is "structure". Structure is a user-defined data type in C which allows to combine data items/variables of different kinds.
struct Question {
    char text[100]; //Text limit of 100 characters for each question
    char options[4][40]; //Options limit of 4 options with 40 characters for each option
    char correct; //Stores the letter ('A', 'B', 'C' or 'D') of the correct option
};
 
 
//Array structure to hold all the questions and their options
struct Question quiz[TOTAL] = {
//"quiz" is an array of user defined datatype "Question" which holds the questions and their options. Each question is stored as a structure with its text, options, and correct answer.
 
    // {"Question", {"option1", "option2", "option3", "option4"}, 'correct_option'},-----We shall use this format to frame the questions.
    // PLACEHOLDER questions below - replace them after the team finalizes the questions.
    // Keep exactly TOTAL (5) entries and 'correct_option' as an uppercase 'A', 'B', 'C' or 'D'.
 
    {"Which header file is needed for printf()?", {"stdlib.h", "stdio.h", "string.h", "math.h"}, 'B'},
    {"Which symbol ends a statement in C?", {";", ":", ".", ","}, 'A'},
    {"Which keyword is used to define a structure?", {"class", "union", "struct", "object"}, 'C'},
    {"Which function is used to open a file in C?", {"open()", "fread()", "fscanf()", "fopen()"}, 'D'},
    {"Which format specifier prints an integer?", {"%d", "%f", "%c", "%s"}, 'A'},
 
};
 
//clearLine() removes any leftover characters (like the Enter key) that are still waiting in the input. Without this, the leftovers would be read by the next scanf() and cause wrong input.
void clearLine(void)                      /* throw away the rest of the line */
{
    int ch;                               /* int, because getchar() returns an int */
    //getchar() reads one character at a time. The loop keeps reading until it reaches the end of the line ('\n') or the end of the input (EOF). The empty ";" means nothing else needs to be done in each round.
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}
 
//getChoice() reads the number typed in the main menu and gives it back to main(). It returns 0 if the input is not a number, so main() can show "Invalid choice".
int getChoice(void)                       /* read a menu number safely */
{
    int choice = 0;                       /* 0 = invalid */
    //scanf() reads the number into "choice". It returns EOF when there is no more input (for example, when the input is closed), so we exit the menu instead of looping forever.
    if (scanf("%d", &choice) == EOF)
        return 3;                         /* input ended: exit */
    clearLine();                          //Discards anything extra typed after the number
    return choice;
}
 
//getAnswer() asks for the player's answer and repeats until a valid option (A, B, C or D) is entered. Small letters are accepted too, because they are converted to capital letters.
char getAnswer(void)                      /* keep asking until A, B, C or D */
{
    char c;
    //"while (1)" is a loop that never stops by itself. It ends only when the return statement is reached.
    while (1) {
        printf("  Your answer (A-D): ");
        //The space before %c in " %c" skips any spaces or blank lines before the letter.
        if (scanf(" %c", &c) != 1)
            return '\0';                 /* input ended */
        clearLine();                      //Discards anything extra typed after the letter
        //In the ASCII table, a small letter is exactly 32 more than its capital letter, so subtracting 32 converts it (a -> A).
        if (c >= 'a' && c <= 'z')
            c = c - 32;                   /* lower case -> upper case */
        if (c >= 'A' && c <= 'D')
            return c;                     //Valid answer, so send it back to playQuiz()
        printf("  Invalid input. Please enter A, B, C or D.\n");
    }
}
 
//saveScore() adds the player's name and score as a new line at the end of the scores file, so the scores of earlier players are not lost.
void saveScore(const char *name, int score)
{
    //fopen() opens the file. "a" is the append mode: it adds to the end of the file and creates the file if it does not exist yet.
    FILE *fp = fopen(SCORE_FILE, "a");
    //If the file could not be opened, fopen() returns NULL, so we show a message and stop instead of crashing.
    if (fp == NULL) {
        printf("  Could not save the score.\n");
        return;
    }
    //fprintf() works like printf() but writes into the file. "%-20s" keeps the name in a 20 character wide column so the scores line up neatly.
    fprintf(fp, "%-20s %d / %d\n", name, score, TOTAL);
    fclose(fp);                           //Closes the file so that the data is safely saved
}
 
//playQuiz() runs one full round of the quiz: it asks the name, shows every question, checks each answer, then shows and saves the final score.
void playQuiz(void)
{
    char name[30]; //Stores the player's name (up to 29 characters, the last space is kept for the end-of-string character '\0')
    int score = 0; //Counts the correct answers, it starts from 0
 
    printf("\n  Enter your name: ");
    //"%29s" reads one word and stops after 29 characters so that the name array can never overflow.
    if (scanf("%29s", name) != 1)
        return;
    clearLine();
 
    //This loop runs once for every question, from the first question (i = 0) to the last one.
    for (int i = 0; i < TOTAL; i++) {
        printf("\n  ------------------------------------------\n");
        printf("  Question %d of %d\n", i + 1, TOTAL); //i starts from 0, so i + 1 is used to show the human-friendly question number
        printf("  %s\n\n", quiz[i].text);
        //Prints the 4 options. 'A' + j gives the letters A, B, C, D one after the other (j = 0, 1, 2, 3).
        for (int j = 0; j < 4; j++)
            printf("     %c) %s\n", 'A' + j, quiz[i].options[j]);
        printf("\n");
 
        char answer = getAnswer();
        if (answer == '\0')
            return;                       /* input ended */
        //Compares the player's answer with the correct answer stored for this question
        if (answer == quiz[i].correct) {
            printf("  [+] Correct!\n");
            score++;                      //Adds 1 to the score for every correct answer
        } else {
            printf("  [x] Wrong. The answer is %c.\n", quiz[i].correct);
        }
    }
 
    //Final result. The percentage is calculated as (score x 100) / TOTAL.
    printf("\n  ==========================================\n");
    printf("   RESULT: %s\n", name);
    printf("   Score : %d / %d  (%d%%)\n", score, TOTAL, score * 100 / TOTAL);
    printf("  ==========================================\n");
    saveScore(name, score);               //Stores this result in the scores file
}
 
//showScores() reads the scores file line by line and prints every saved score on the screen.
void showScores(void)
{
    char line[100]; //Temporary space to hold one line of the file at a time
    FILE *fp = fopen(SCORE_FILE, "r"); //"r" is the read mode: it opens the file only for reading
 
    printf("\n  ============= HIGH SCORES ================\n");
    //If the file does not exist yet, fopen() returns NULL, which means no one has played the quiz so far.
    if (fp == NULL) {
        printf("   No scores recorded yet.\n");
    } else {
        //fgets() reads one line from the file each time and returns NULL when there are no more lines, which ends the loop.
        while (fgets(line, sizeof line, fp) != NULL)
            printf("   %s", line);
        fclose(fp);
    }
    printf("  ==========================================\n");
}
 
//main() is where the program starts. It shows the menu again and again until the user chooses Exit.
int main(void)
{
    int choice; //Stores the menu option chosen by the user
    //do-while runs the menu at least once and repeats it as long as the choice is not 3 (Exit).
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
        //Calls the function that matches the user's choice. Anything other than 1, 2 or 3 shows an error message.
        if (choice == 1)
            playQuiz();
        else if (choice == 2)
            showScores();
        else if (choice == 3)
            printf("\n  Goodbye!\n\n");
        else
            printf("\n  Invalid choice. Please enter 1, 2 or 3.\n");
    } while (choice != 3);
 
    return 0; //0 tells the operating system that the program finished without any error
}
 
