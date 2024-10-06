#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100//LimIt cause nobody seein

char fileNames[MAX_FILES][100];
int fileCount = 0;//counting of the files

void addtxt(char *filename) //this adds .txt after every filename because mai dalna bhul gya
{
    if (strstr(filename, ".txt") == NULL) 
    {
        strcat(filename, ".txt");
    }
}

void createF() {//this creates a file
    FILE *file;
    char filename[100];
    
    if (fileCount >= MAX_FILES) //limit ke ANDAR
    {
        printf("Error: Maximum file limit reached. Cannot create more files.\n");
        return;
    }
    
    printf("\nEnter the name of the file: ");
    scanf("%s", filename);
    
    addtxt(filename);//ye sab jagah dikhega .txt jo add karna hai
    
    file = fopen(filename, "w");
    if (file == NULL) //file ka naam nahi dala to??
    {
        printf("Error creating file: %s\n", filename);
        return;
    }
    
    strcpy(fileNames[fileCount], filename);//basically copy karta hai
    fileCount++;
    
    printf("File created successfully: %s\n", filename);//hogya
    fclose(file);
}

void writeF() //file ke andar kuch likhna to hoga na
{
    FILE *file;
    char filename[100];
    char content[500];
    printf("\nEnter the name of the file to write: ");
    scanf("%s", filename);
    
    addtxt(filename);
    
    file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }
    printf("Enter content (end input by pressing Enter):\n");
    scanf(" %[^\n]s", content);
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content written to file: %s\n", filename);
}

void appendF() //content add karne ke liye koi file mai
{
    FILE *file;
    char filename[100];
    char content[500];
    printf("\nEnter the name of the file to append: ");
    scanf("%s", filename);
    
    addtxt(filename);//wheeee
    
    file = fopen(filename, "a");
    if (file == NULL) 
    {
        printf("No file found.\n");
        return;
    }
    printf("Enter content to append (end input by pressing Enter):\n");
    scanf(" %[^\n]s", content);
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content appended to file: %s\n", filename);
}

void readF() //padhega likhega tabhi to badega
{
    FILE *file;
    char filename[100];
    char content[500];
    printf("\nEnter the name of the file to read: ");
    scanf("%s", filename);
    
    addtxt(filename);
    
    file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("No file found.\n");
        return;
    }
    printf("\n--- Reading from file: %s ---\n", filename);
    while (fgets(content, 500, file) != NULL) 
    {
        printf("%s", content);
    }
    printf("\n--- End of file ---\n");
    fclose(file);
}

void deleteF() //delete
{
    char filename[100];
    printf("\nEnter the name of the file to delete: ");
    scanf("%s", filename);
    
    addtxt(filename);
    
    if (remove(filename) == 0) 
    {
        printf("File deleted successfully: %s\n", filename);
        
        for (int i = 0; i < fileCount; i++) 
        {
            if (strcmp(fileNames[i], filename) == 0) 
            {
                for (int j = i; j < fileCount - 1; j++) 
                {
                    strcpy(fileNames[j], fileNames[j + 1]);
                }
                fileCount--;
                break;
            }
        }
    } else 
    {
        perror("Error deleting file");
    }
}

void showFileNames()//naaam dekho
{
    if (fileCount == 0) 
    {
        printf("\nNo .txt files have been created yet.\n");
    } else 
    {
        printf("\nList of created .txt files:\n");
        for (int i = 0; i < fileCount; i++) 
        {
            printf("%d. %s\n", i + 1, fileNames[i]);
        }
    }
}

int main() {
    int choice;
    while (1) 
    {
        printf("\n=============================\n");
        printf("      File Manipulation App\n");
        printf("=============================\n");
        printf("1. Create a file\n");
        printf("2. Write to a file (overwrite)\n");
        printf("3. Read from a file\n");
        printf("4. Append to a file\n");
        printf("5. Delete a file\n");
        printf("6. Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) //the best yoaimo
        {
            case 1:
                createF();
                break;
            case 2:
                writeF();
                break;
            case 3:
                readF();
                break;
            case 4:
                appendF();
                break;
            case 5:
                deleteF();
                break;
            case 6:
                printf("\nExiting the program... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

        showFileNames();
    }
    return 0;
}
