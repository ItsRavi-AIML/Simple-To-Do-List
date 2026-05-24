/*
===========================================
        SIMPLE TO-DO LIST IN C
===========================================

Features:
- Add Tasks
- View Tasks
- Edit Tasks
- Delete Tasks
- Mark Tasks Complete
- Save & Load Tasks

Developed Using:
- C Language
- File Handling
- Structures
- Arrays
- Functions

===========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

struct Task {
    char title[MAX_LENGTH];
    int completed;
};

struct Task tasks[MAX_TASKS];
int taskCount = 0;

// Function declarations
void addTask();
void viewTasks();
void markComplete();
void editTask();
void deleteTask();
void clearScreen();
void pauseScreen();
void saveTasks();
void loadTasks();

int main() {
    int choice;

    loadTasks();

    while (1) {
        clearScreen();

printf("\n");
printf("=====================================\n");
printf("         SIMPLE TO-DO LIST\n");
printf("=====================================\n");

int completed = 0;

for(int i = 0; i < taskCount; i++) {

    if(tasks[i].completed) {
        completed++;
    }
}

printf("Total Tasks     : %d\n", taskCount);
printf("Completed Tasks : %d\n", completed);
printf("Pending Tasks   : %d\n",
       taskCount - completed);

printf("=====================================\n");
printf("1. Add Task\n");
printf("2. View Tasks\n");
printf("3. Mark Task as Complete\n");
printf("4. Edit Task\n");
printf("5. Delete Task\n");
printf("6. Exit\n");
printf("=====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                markComplete();
                break;

            case 4:
                editTask();
                break;

            case 5:
                deleteTask();
                break;

            case 6:
                printf("\nThank you for using Simple To-Do List!\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
                pauseScreen();
        }
    }

    return 0;
}

void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("\nTask list is full!\n");
        pauseScreen();
        return;
    }

    printf("\nEnter task: ");
    fgets(tasks[taskCount].title, MAX_LENGTH, stdin);

    // Remove newline
    tasks[taskCount].title[strcspn(tasks[taskCount].title, "\n")] = '\0';

    tasks[taskCount].completed = 0;
    taskCount++;
    saveTasks();

    printf("\nTask added successfully!\n");
    pauseScreen();
}

void viewTasks() {
    printf("\n========== TASK LIST ==========\n");

    if (taskCount == 0) {
        printf("No tasks available.\n");
    } else {
        for (int i = 0; i < taskCount; i++) {
            printf("%d. [%c] %s\n",
                   i + 1,
                   tasks[i].completed ? 'X' : ' ',
                   tasks[i].title);
        }
    }

    printf("================================\n");
    pauseScreen();
}

void markComplete() {
    int num;

    viewTasks();

    if (taskCount == 0)
        return;

    printf("\nEnter task number to mark complete: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("\nInvalid task number!\n");
    } else {
        tasks[num - 1].completed = 1;
        saveTasks();
        printf("\nTask marked as complete!\n");
    }

    pauseScreen();
}

void editTask() {

    int num;

    viewTasks();

    if (taskCount == 0)
        return;

    printf("\nEnter task number to edit: ");
    scanf("%d", &num);
    getchar();

    if (num < 1 || num > taskCount) {

        printf("\nInvalid task number!\n");

    } else {

        printf("Enter new task: ");

        fgets(tasks[num - 1].title,
              MAX_LENGTH,
              stdin);

        tasks[num - 1].title[
            strcspn(tasks[num - 1].title, "\n")
        ] = '\0';

        saveTasks();

        printf("\nTask updated successfully!\n");
    }

    pauseScreen();
}
void deleteTask() {
    int num;

    viewTasks();

    if (taskCount == 0)
        return;

    printf("\nEnter task number to delete: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("\nInvalid task number!\n");
    } else {

        for (int i = num - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }

        taskCount--;
        saveTasks();

        printf("\nTask deleted successfully!\n");
    }

    pauseScreen();
}

void clearScreen() {
    system("cls"); // Windows
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
}

void saveTasks() {

    FILE *file = fopen("tasks.txt", "w");

    if (file == NULL) {
        printf("Error saving tasks!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {

        fprintf(file,
                "%s|%d\n",
                tasks[i].title,
                tasks[i].completed);
    }

    fclose(file);
}

void loadTasks() {

    FILE *file = fopen("tasks.txt", "r");

    if (file == NULL)
        return;

    while (
        fscanf(file,
               " %99[^|]|%d\n",
               tasks[taskCount].title,
               &tasks[taskCount].completed) == 2
    ) {

        taskCount++;

        if (taskCount >= MAX_TASKS)
            break;
    }

    fclose(file);
}