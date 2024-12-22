#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 100
#define MAX_OPTIONS_LENGTH 100

struct Question {
    int number;
    char body[256];
    char optionA[MAX_OPTIONS_LENGTH];
    char optionB[MAX_OPTIONS_LENGTH];
    char optionC[MAX_OPTIONS_LENGTH];
    char optionD[MAX_OPTIONS_LENGTH];
    char answer;
};

struct Question_Bank {
    struct Question questions[MAX_QUESTIONS];
    int count;
};

// Function prototypes
void read_questions_from_file(struct Question_Bank *bank, char *filename);
void initialize_question(struct Question *question, int number, const char *body,
                         const char *optionA, const char *optionB,
                         const char *optionC, const char *optionD, char answer);
void generate_booklets(struct Question_Bank *bank, int booklets, int questions_per_booklet);
void shuffle_options(char options[][MAX_OPTIONS_LENGTH], int num_options);
void shuffle_questions(struct Question_Bank *bank);
void print_booklet(struct Question_Bank *booklet);

// Function to initialize a question
void initialize_question(struct Question *question, int number, const char *body,
                         const char *optionA, const char *optionB,
                         const char *optionC, const char *optionD, char answer) {
    question->number = number;
    strcpy(question->body, body);
    strcpy(question->optionA, optionA);
    strcpy(question->optionB, optionB);
    strcpy(question->optionC, optionC);
    strcpy(question->optionD, optionD);
    question->answer = answer;
}

// Function to read questions from a file and allocate memory
void read_questions_from_file(struct Question_Bank *bank, char *filename) {
    // Implementation to read questions from a file and populate the bank
    // Let's use a placeholder
    bank->count = 5;
    for (int i = 0; i < bank->count; i++) {
        struct Question *current_question = &bank->questions[i];
        initialize_question(current_question, i + 1,
                            "Question body", "Option A", "Option B", "Option C", "Option D", 'A' + i % 4);
    }
}

// Function to shuffle options
void shuffle_options(char options[][MAX_OPTIONS_LENGTH], int num_options) {
    srand(time(NULL)); // Initialize random seed

    for (int i = num_options - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Swap options[i] and options[j]
        char temp[MAX_OPTIONS_LENGTH];
        strcpy(temp, options[i]);
        strcpy(options[i], options[j]);
        strcpy(options[j], temp);
    }
}

// Function to shuffle questions in a bank
void shuffle_questions(struct Question_Bank *bank) {
    srand(time(NULL)); // Initialize random seed

    for (int i = bank->count - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Swap questions[i] and questions[j]
        struct Question temp = bank->questions[i];
        bank->questions[i] = bank->questions[j];
        bank->questions[j] = temp;
    }
}

// Function to generate booklets
void generate_booklets(struct Question_Bank *bank, int booklets, int questions_per_booklet) {
    // Shuffle the questions before generating booklets
    shuffle_questions(bank);

    for (int i = 0; i < booklets; i++) {
        struct Question_Bank booklet;
        booklet.count = questions_per_booklet;

        // Copy questions to the booklet
        for (int j = 0; j < questions_per_booklet; j++) {
            memcpy(&booklet.questions[j], &bank->questions[i * questions_per_booklet + j], sizeof(struct Question));
        }

        // Shuffle options within each question in the booklet
        for (int j = 0; j < questions_per_booklet; j++) {
            char options[4][MAX_OPTIONS_LENGTH] = {
                booklet.questions[j].optionA,
                booklet.questions[j].optionB,
                booklet.questions[j].optionC,
                booklet.questions[j].optionD
            };
            shuffle_options(options, 4);
            // Update options in the booklet
            sprintf(booklet.questions[j].optionA, "%s", options[0]);
            sprintf(booklet.questions[j].optionB, "%s", options[1]);
            sprintf(booklet.questions[j].optionC, "%s", options[2]);
            sprintf(booklet.questions[j].optionD, "%s", options[3]);
        }

        // Print the generated booklet
        printf("\nBooklet %d:\n", i + 1);
        print_booklet(&booklet);
    }
}

// Function to print a booklet
void print_booklet(struct Question_Bank *booklet) {
    for (int i = 0; i < booklet->count; i++) {
        printf("Q%d: %s\n", booklet->questions[i].number, booklet->questions[i].body);
        printf("  A: %s\n", booklet->questions[i].optionA);
        printf("  B: %s\n", booklet->questions[i].optionB);
        printf("  C: %s\n", booklet->questions[i].optionC);
        printf("  D: %s\n", booklet->questions[i].optionD);
        printf("  Answer: %c\n\n", booklet->questions[i].answer);
    }
}

int main() {
    struct Question_Bank bank;
    char filename[100];
    int booklets, questions_per_booklet;

    // Get input filename
    printf("Enter input file name: ");
    scanf("%s", filename);

    // Read questions from file
    read_questions_from_file(&bank, filename);

    // Get user input for booklets and questions per booklet
    printf("Enter number of booklets: ");
    scanf("%d", &booklets);
    printf("Enter number of questions per booklet: ");
    scanf("%d", &questions_per_booklet);

    // Generate booklets
    generate_booklets(&bank, booklets, questions_per_booklet);

    return 0;
}
