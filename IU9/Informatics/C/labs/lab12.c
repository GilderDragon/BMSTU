#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 25


bool read(FILE* file, char* word) {
    int char_index = 0;
    bool inWord = false;
    int ch;

    word[0] = '\0';

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            if (char_index < MAX_WORD_LENGTH - 1) {
                word[char_index] = (char)ch;
                char_index++;
            }
            inWord = true;
        } else if (inWord) {
            word[char_index] = '\0';
            return true;
        }
    }

    if (inWord) {
        word[char_index] = '\0';
        return true;
    }

    return false;
}


bool isPalindrome(char* word) {
    int len = 0;
    while (word[len] != '\0') {
        len++;
    }
    for (int i = 0; i < len / 2; i++) {
        if (word[i] != word[len - i - 1]) {
            return false;
        }
    }
    return true;
}


int main() {
    char path[] = "lab12.txt";

    FILE* file = fopen(path, "r");

    char word[MAX_WORD_LENGTH + 1];

    bool anyPalindrome = false;

    while (read(file, word)) {
        if (isPalindrome(word)) {
            anyPalindrome = true;
            printf("%s ", word);
        }
    }

    if (!anyPalindrome) {
        printf("No palindromes in the file");
    }

    fclose(file);

    return 0;
}