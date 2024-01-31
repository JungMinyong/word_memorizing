#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_LINE_LENGTH 1024
#define MAX_WORDS 1000 // Adjust this based on the expected number of entries

typedef struct {
    char word[MAX_LINE_LENGTH];
    char meaning[MAX_LINE_LENGTH];
    int correct;
    int incorrect;
} DictionaryEntry;

int read_voca(DictionaryEntry * dictionary, int max_words) {
    FILE *file = fopen("voca.csv", "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return -1;
    }

    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && count < max_words) {
        line[strcspn(line, "\n")] = 0;

        char *word = strtok(line, ",");
        char *meaning = strtok(NULL, ",");

        if (!(word && meaning)) {
            printf("Invalid line: %s\n", line);
            continue;
        }

        strncpy(dictionary[count].word, word, sizeof(dictionary[count].word));
        strncpy(dictionary[count].meaning, meaning, sizeof(dictionary[count].meaning));
        dictionary[count].correct = 0;
        dictionary[count].incorrect = 1;
        count++;
    }

    fclose(file);
    return count;
}


int main() {
    DictionaryEntry dictionary[MAX_WORDS];
    int count = read_voca(dictionary, MAX_WORDS);

    if (count < 0) {
        return 1;
    }
    else if (count == 0){
        printf("No words in the dictionary.\n");
        return 1;
    }
    printf("================================\n");
    printf("Successfully load the dictionary\n");
    printf("================================\n");

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // pick a random one
    int test = 0;
    while (test < 3){
    int randomIndex = rand() % count;
    printf("Random Word: %s, Meaning: %s\n", dictionary[randomIndex].word, dictionary[randomIndex].meaning);
    test++;
}

    return 0;
}