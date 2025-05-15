#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "filedata.txt"

void createFile();
void writeFile();
void readFile();
void appendFile();
void deleteFile();

int main() {
    int choice;
    while (1) {
        printf("\nFile Operations Menu:\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Append to File\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        
        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                writeFile();
                break;
            case 3:
                readFile();
                break;
            case 4:
                appendFile();
                break;
            case 5:
                deleteFile();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void createFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    printf("File created successfully.\n");
    fclose(file);
}

void writeFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char content[256];
    printf("Enter content to write: ");
    fgets(content, sizeof(content), stdin);
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content written successfully.\n");
}

void readFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File does not exist or cannot be opened!\n");
        return;
    }
    char ch;
    printf("File content:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void appendFile() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char content[256];
    printf("Enter content to append: ");
    fgets(content, sizeof(content), stdin);
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content appended successfully.\n");
}

void deleteFile() {
    if (remove(FILENAME) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file!\n");
    }
}

