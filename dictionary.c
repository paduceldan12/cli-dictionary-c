#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50
#define MAX_DEF_LEN 200
#define DICTIONARY_FILE "dictionary.txt"

// Function to add a new word to the dictionary
void add_word() {
    char word[MAX_WORD_LEN], definition[MAX_DEF_LEN];
    FILE *file = fopen(DICTIONARY_FILE, "a");

    if (!file) {
        perror("Error opening dictionary file");
        return;
    }

    printf("Enter the word: ");
    scanf(" %[^\n]", word);
    printf("Enter the definition: ");
    scanf(" %[^\n]", definition);

    fprintf(file, "%s:%s\n", word, definition);
    fclose(file);
    printf("Word added successfully!\n");
}

// Function to search for a word in the dictionary
void search_word() {
    char word[MAX_WORD_LEN], file_word[MAX_WORD_LEN], file_def[MAX_DEF_LEN];
    int found = 0;
    FILE *file = fopen(DICTIONARY_FILE, "r");

    if (!file) {
        perror("Error opening dictionary file");
        return;
    }

    printf("Enter the word to search: ");
    scanf(" %[^\n]", word);

    while (fscanf(file, "%[^:]:%[^\n]\n", file_word, file_def) != EOF) {
        if (strcmp(word, file_word) == 0) {
            printf("Definition: %s\n", file_def);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Word not found in dictionary.\n");

    fclose(file);
}

// Function to update a word's definition
void update_word() {
    char word[MAX_WORD_LEN], new_def[MAX_DEF_LEN], file_word[MAX_WORD_LEN], file_def[MAX_DEF_LEN];
    int found = 0;
    FILE *file = fopen(DICTIONARY_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Error opening file");
        return;
    }

    printf("Enter the word to update: ");
    scanf(" %[^\n]", word);

    while (fscanf(file, "%[^:]:%[^\n]\n", file_word, file_def) != EOF) {
        if (strcmp(word, file_word) == 0) {
            printf("Enter the new definition: ");
            scanf(" %[^\n]", new_def);
            fprintf(temp, "%s:%s\n", file_word, new_def);
            found = 1;
        } else {
            fprintf(temp, "%s:%s\n", file_word, file_def);
        }
    }

    fclose(file);
    fclose(temp);

    remove(DICTIONARY_FILE);
    rename("temp.txt", DICTIONARY_FILE);

    if (found)
        printf("Word updated successfully!\n");
    else
        printf("Word not found.\n");
}

// Function to delete a word from the dictionary
void delete_word() {
    char word[MAX_WORD_LEN], file_word[MAX_WORD_LEN], file_def[MAX_DEF_LEN];
    int found = 0;
    FILE *file = fopen(DICTIONARY_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Error opening file");
        return;
    }

    printf("Enter the word to delete: ");
    scanf(" %[^\n]", word);

    while (fscanf(file, "%[^:]:%[^\n]\n", file_word, file_def) != EOF) {
        if (strcmp(word, file_word) != 0) {
            fprintf(temp, "%s:%s\n", file_word, file_def);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(DICTIONARY_FILE);
    rename("temp.txt", DICTIONARY_FILE);

    if (found)
        printf("Word deleted successfully!\n");
    else
        printf("Word not found.\n");
}

// Function to display all words in the dictionary
void display_dictionary() {
    char file_word[MAX_WORD_LEN], file_def[MAX_DEF_LEN];
    FILE *file = fopen(DICTIONARY_FILE, "r");

    if (!file) {
        perror("Error opening dictionary file");
        return;
    }

    printf("\n--- Dictionary Entries ---\n");
    while (fscanf(file, "%[^:]:%[^\n]\n", file_word, file_def) != EOF) {
        printf("%s: %s\n", file_word, file_def);
    }
    fclose(file);
}

// Main menu function
void menu() {
    int choice;

    while (1) {
        printf("\n===== Command Line Dictionary =====\n");
        printf("1. Add a word\n");
        printf("2. Search for a word\n");
        printf("3. Update a word\n");
        printf("4. Delete a word\n");
        printf("5. Display all words\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_word(); break;
            case 2: search_word(); break;
            case 3: update_word(); break;
            case 4: delete_word(); break;
            case 5: display_dictionary(); break;
            case 6: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
