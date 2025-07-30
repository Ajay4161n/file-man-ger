#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to create a file
void create_file(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not create file.\n");
        return;
    }
    printf("File '%s' created successfully.\n", filename);
    fclose(fp);
}

// Function to read contents of a file
void read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: File '%s' not found.\n", filename);
        return;
    }

    char ch;
    printf("Contents of '%s':\n", filename);
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
    printf("\n");
}

// Function to delete a file
void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error: Could not delete '%s'.\n", filename);
    }
}

// Function to list all regular files in the current directory
void list_files(const char *path) {
    DIR *d;
    struct dirent *entry;

    d = opendir(path);
    if (d == NULL) {
        printf("Could not open directory '%s'.\n", path);
        return;
    }

    printf("Files in directory '%s':\n", path);

    while ((entry = readdir(d)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Build full path
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s\\%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == 0) {
            if (S_ISREG(file_stat.st_mode)) {
                printf("  %s\n", entry->d_name);
            }
        }
    }

    closedir(d);
}

int main() {
    int choice;
    char filename[256];

    while (1) {
        printf("\n====== File Manager ======\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Delete File\n");
        printf("4. List Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter file name to create: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // remove newline
                create_file(filename);
                break;

            case 2:
                printf("Enter file name to read: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                read_file(filename);
                break;

            case 3:
                printf("Enter file name to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                delete_file(filename);
                break;

            case 4:
                list_files(".");
                break;

            case 5:
                printf("Exiting File Manager. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
