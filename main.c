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
#include <windows.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

struct Task {
    char title[MAX_LENGTH];
    int completed;
};

struct Task tasks[MAX_TASKS];
int taskCount = 0;

/* Function Declarations */
void addTask();
void viewTasks();
void markComplete();
void editTask();
void deleteTask();
void clearScreen();
void pauseScreen();
void saveTasks();
void loadTasks();
void setColor(int color);

/* Color Function */
void setColor(int color) {
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
}

int main() {

    int choice;

    loadTasks();

    while (1) {

        clearScreen();

        int completed = 0;

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].completed) {
                completed++;
            }
        }

        /* Title */
        setColor(11);
        printf("\n");
        printf("=====================================\n");
        printf("         SIMPLE TO-DO LIST\n");
        printf("=====================================\n");

        /* Statistics */
        setColor(14);
        printf("Total Tasks     : %d\n", taskCount);
        printf("Completed Tasks : %d\n", completed);
        printf("Pending Tasks   : %d\n",
               taskCount - completed);

        /* Menu */
        setColor(11);
        printf("=====================================\n");

        setColor(15);
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Complete\n");
        printf("4. Edit Task\n");
        printf("5. Delete Task\n");
        printf("6. Exit\n");

        setColor(11);
        printf("=====================================\n");

        setColor(14);
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

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
                setColor(10);
                printf("\nThank you for using Simple To-Do List!\n");
                setColor(15);
                return 0;

            default:
                setColor(12);
                printf("\nInvalid choice!\n");
                setColor(15);
                pauseScreen();
        }
    }

    return 0;
}

/* Add Task */
void addTask() {

    if (taskCount >= MAX_TASKS) {

        setColor(12);
        printf("\nTask list is full!\n");
        setColor(15);

        pauseScreen();
        return;
    }

    setColor(14);
    printf("\nEnter task: ");

    fgets(tasks[taskCount].title,
          MAX_LENGTH,
          stdin);

    tasks[taskCount].title[
        strcspn(tasks[taskCount].title, "\n")
    ] = '\0';

    tasks[taskCount].completed = 0;

    taskCount++;

    saveTasks();

    setColor(10);
    printf("\nTask added successfully!\n");
    setColor(15);

    pauseScreen();
}

/* View Tasks */
void viewTasks() {

    setColor(11);

    printf("\n========== TASK LIST ==========\n");

    if (taskCount == 0) {

        setColor(12);
        printf("No tasks available.\n");

    } else {

        for (int i = 0; i < taskCount; i++) {

            if (tasks[i].completed)
                setColor(10);
            else
                setColor(15);

            printf("%d. [%c] %s\n",
                   i + 1,
                   tasks[i].completed ? 'X' : ' ',
                   tasks[i].title);
        }
    }

    setColor(11);
    printf("================================\n");

    setColor(15);

    pauseScreen();
}

/* Mark Complete */
void markComplete() {

    int num;

    viewTasks();

    if (taskCount == 0)
        return;

    setColor(14);
    printf("\nEnter task number to mark complete: ");

    scanf("%d", &num);
    getchar();

    if (num < 1 || num > taskCount) {

        setColor(12);
        printf("\nInvalid task number!\n");

    } else {

        tasks[num - 1].completed = 1;

        saveTasks();

        setColor(10);
        printf("\nTask marked as complete!\n");
    }

    setColor(15);

    pauseScreen();
}

/* Edit Task */
void editTask() {

    int num;

    viewTasks();

    if (taskCount == 0)
        return;

    setColor(14);
    printf("\nEnter task number to edit: ");

    scanf("%d", &num);
    getchar();

    if (num < 1 || num > taskCount) {

        setColor(12);
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

        setColor(10);
        printf("\nTask updated successfully!\n");
    }

    setColor(15);

    pauseScreen();
}

/* Delete Task */
void deleteTask() {

    int num;

    viewTasks();

    if (taskCount == 0)
        return;

    setColor(14);
    printf("\nEnter task number to delete: ");

    scanf("%d", &num);
    getchar();

    if (num < 1 || num > taskCount) {

        setColor(12);
        printf("\nInvalid task number!\n");

    } else {

        for (int i = num - 1;
             i < taskCount - 1;
             i++) {

            tasks[i] = tasks[i + 1];
        }

        taskCount--;

        saveTasks();

        setColor(10);
        printf("\nTask deleted successfully!\n");
    }

    setColor(15);

    pauseScreen();
}

/* Clear Screen */
void clearScreen() {
    system("cls");
}

/* Pause Screen */
void pauseScreen() {

    setColor(8);

    printf("\nPress Enter to continue...");

    setColor(15);

    getchar();
}

/* Save Tasks */
void saveTasks() {

    FILE *file = fopen("tasks.txt", "w");

    if (file == NULL) {

        setColor(12);
        printf("Error saving tasks!\n");
        setColor(15);

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

/* Load Tasks */
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