#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define clrscr() system("cls")
#else
#include <termios.h>
#include <unistd.h>
#define clrscr() printf("\033[H\033[J")
#endif

struct Node {
    void *data;
    int dataType;
    struct Node *next;
};

struct Node *head = NULL;
int listCreated = 0;
int currentDataType = 0;

#ifdef _WIN32
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

void displayListAfterOperation() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    printf("Current List: ");
    while (temp != NULL) {
        switch (temp->dataType) {
            case 1:
                printf("%d", *(int *)temp->data);
                break;
            case 2:
                printf("%f", *(float *)temp->data);
                break;
            case 3:
                printf("%c", *(char *)temp->data);
                break;
            case 4:
                printf("%s", (char *)temp->data);
                break;
        }
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void createList() {
    clrscr();
    int n, dataType, i;
    printf ("CREATION OF LIST\n");
    printf("Enter the data type (1: Integer, 2: Float, 3: Character, 4: String): ");
    scanf("%d", &dataType);
    printf("\n\nEnter the number of nodes: ");
    scanf("%d", &n);
    printf("\n");
    getchar();

    if (n <= 0) {
        return;
    }

    currentDataType = dataType;

    head = (struct Node *)malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    head->dataType = dataType;
    head->next = NULL;

    switch (dataType) {
        case 1: {
            int value;
            printf("Enter data for node 1: ");
            scanf("%d", &value);
            head->data = malloc(sizeof(int));
            *(int *)head->data = value;
            break;
        }
        case 2: {
            float value;
            printf("Enter data for node 1: ");
            scanf("%f", &value);
            head->data = malloc(sizeof(float));
            *(float *)head->data = value;
            break;
        }
        case 3: {
            char value;
            printf("Enter data for node 1: ");
            scanf("%c", &value);
            getchar();
            head->data = malloc(sizeof(char));
            *(char *)head->data = value;
            break;
        }
        case 4: {
            char value[100];
            printf("Enter data for node 1: ");
            fgets(value, sizeof(value), stdin);
            value[strcspn(value, "\n")] = 0;
            head->data = malloc(strlen(value) + 1);
            strcpy((char *)head->data, value);
            break;
        }
    }

    struct Node *temp = head;
    i = 2;
    while (i <= n) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("\nMemory allocation failed.\n");
            return;
        }
        newNode->dataType = dataType;
        newNode->next = NULL;

        switch (dataType) {
            case 1: {
                int value;
                printf("Enter data for node %d: ", i);
                scanf("%d", &value);
                newNode->data = malloc(sizeof(int));
                *(int *)newNode->data = value;
                break;
            }
            case 2: {
                float value;
                printf("Enter data for node %d: ", i);
                scanf("%f", &value);
                newNode->data = malloc(sizeof(float));
                *(float *)newNode->data = value;
                break;
            }
            case 3: {
                char value;
                printf("Enter data for node %d: ", i);
                scanf("%c", &value);
                getchar();
                newNode->data = malloc(sizeof(char));
                *(char *)newNode->data = value;
                break;
            }
            case 4: {
                char value[100];
                printf("Enter data for node %d: ", i);
                fgets(value, sizeof(value), stdin);
                value[strcspn(value, "\n")] = 0;
                newNode->data = malloc(strlen(value) + 1);
                strcpy((char *)newNode->data, value);
                break;
            }
        }

        temp->next = newNode;
        temp = newNode;
        i++;
    }
    printf("\nList created.\n");
    listCreated = 1;
    displayListAfterOperation();
    switch (currentDataType) {
        case 1: printf("\nData Type is: Integer\n"); break;
        case 2: printf("\nData Type is: Float\n"); break;
        case 3: printf("\nData Type is: Character\n"); break;
        case 4: printf("\nData Type is: String\n"); break;
    }
}

void traverseList() {
    clrscr();
    if (head == NULL) {
        printf("\nList is empty.\n");
        return;
    }
    displayListAfterOperation();
}

void insertAtStart() {
    clrscr();
    if (head == NULL) {
        printf("List is empty, create a list first.\n");
        return;
    }
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    newNode->dataType = currentDataType;
    newNode->next = head;

    switch (currentDataType) {
        case 1: {
            int value;
            printf("Enter value to insert: ");
            scanf("%d", &value);
            newNode->data = malloc(sizeof(int));
            *(int *)newNode->data = value;
            break;
        }
        case 2: {
            float value;
            printf("Enter value to insert: ");
            scanf("%f", &value);
            newNode->data = malloc(sizeof(float));
            *(float *)newNode->data = value;
            break;
        }
        case 3: {
            char value;
            printf("Enter value to insert: ");
            scanf("%c", &value);
            getchar();
            newNode->data = malloc(sizeof(char));
            *(char *)newNode->data = value;
            break;
        }
        case 4: {
            char value[100];
            printf("Enter value to insert: ");
            fgets(value, sizeof(value), stdin);
            value[strcspn(value, "\n")] = 0;
            newNode->data = malloc(strlen(value) + 1);
            strcpy((char *)newNode->data, value);
            break;
        }
    }
    head = newNode;
    printf("\nNode inserted at the start.\n");
    displayListAfterOperation();
}

void insertAtEnd() {
    clrscr();
    if (head == NULL) {
        printf("List is empty, create a list first.\n");
        return;
    }
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    newNode->dataType = currentDataType;
    newNode->next = NULL;

    switch (currentDataType) {
        case 1: {
            int value;
            printf("Enter value to insert: ");
            scanf("%d", &value);
            newNode->data = malloc(sizeof(int));
            *(int *)newNode->data = value;
            break;
        }
        case 2: {
        	float value;
            printf("Enter value to insert: ");
            scanf("%f", &value);
            newNode->data = malloc(sizeof(float));
            *(float *)newNode->data = value;
            break;
        }
        case 3: {
            char value;
            printf("Enter value to insert: ");
            scanf("%c", &value);
            getchar();
            newNode->data = malloc(sizeof(char));
            *(char *)newNode->data = value;
            break;
        }
        case 4: {
            char value[100];
            printf("Enter value to insert: ");
            fgets(value, sizeof(value), stdin);
            value[strcspn(value, "\n")] = 0;
            newNode->data = malloc(strlen(value) + 1);
            strcpy((char *)newNode->data, value);
            break;
        }
    }

    if (head == NULL) {
        head = newNode;
        printf("\nNode inserted at the end.\n");
        displayListAfterOperation();
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("\nNode inserted at the end.\n");
    displayListAfterOperation();
}

void insertBeforeValue() {
    clrscr();
    if (head == NULL) {
        printf("List is empty, create a list first.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    newNode->dataType = currentDataType;

    switch (currentDataType) {
        case 1: {
            int newValue, beforeValue;
            printf("Enter value to insert: ");
            scanf("%d", &newValue);
            printf("Enter value before which to insert: ");
            scanf("%d", &beforeValue);
            newNode->data = malloc(sizeof(int));
            *(int *)newNode->data = newValue;

            if (head->dataType == 1 && *(int *)head->data == beforeValue) {
                newNode->next = head;
                head = newNode;
                printf("\nNode inserted before value.\n");
                displayListAfterOperation();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 1 || *(int *)temp->data != beforeValue)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp;
            prev->next = newNode;
            printf("\nNode inserted before value.\n");
            displayListAfterOperation();
            break;
        }
        case 2: {
            float newValue, beforeValue;
            printf("Enter value to insert: ");
            scanf("%f", &newValue);
            printf("Enter value before which to insert: ");
            scanf("%f", &beforeValue);
            newNode->data = malloc(sizeof(float));
            *(float *)newNode->data = newValue;

            if (head->dataType == 2 && *(float *)head->data == beforeValue) {
                newNode->next = head;
                head = newNode;
                printf("\nNode inserted before value.\n");
                displayListAfterOperation();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 2 || *(float *)temp->data != beforeValue)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp;
            prev->next = newNode;
            printf("\nNode inserted before value.\n");
            displayListAfterOperation();
            break;
        }
        case 3: {
            char newValue, beforeValue;
            printf("Enter value to insert: ");
            scanf("%c", &newValue);
            getchar();
            printf("Enter value before which to insert: ");
            scanf("%c", &beforeValue);
            getchar();
            newNode->data = malloc(sizeof(char));
            *(char *)newNode->data = newValue;

            if (head->dataType == 3 && *(char *)head->data == beforeValue) {
                newNode->next = head;
                head = newNode;
                printf("\nNode inserted before value.\n");
                displayListAfterOperation();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 3 || *(char *)temp->data != beforeValue)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp;
            prev->next = newNode;
            printf("\nNode inserted before value.\n");
            displayListAfterOperation();
            break;
        }
        case 4: {
            char newValue[100], beforeValue[100];
            printf("Enter value to insert: ");
            fgets(newValue, sizeof(newValue), stdin);
            newValue[strcspn(newValue, "\n")] = 0;
            printf("Enter value before which to insert: ");
            fgets(beforeValue, sizeof(beforeValue), stdin);
            beforeValue[strcspn(beforeValue, "\n")] = 0;
            newNode->data = malloc(strlen(newValue) + 1);
            strcpy((char *)newNode->data, newValue);

            if (head->dataType == 4 && strcmp((char *)head->data, beforeValue) == 0) {
                newNode->next = head;
                head = newNode;
                printf("\nNode inserted before value.\n");
                displayListAfterOperation();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 4 || strcmp((char *)temp->data, beforeValue) != 0)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp;
            prev->next = newNode;
            printf("\nNode inserted before value.\n");
            displayListAfterOperation();
            break;
        }
    }
}

void insertAfterValue() {
    clrscr();
    if (head == NULL) {
        printf("List is empty, create a list first.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    newNode->dataType = currentDataType;

    switch (currentDataType) {
        case 1: {
            int newValue, afterValue;
            printf("Enter value to insert: ");
            scanf("%d", &newValue);
            printf("Enter value after which to insert: ");
            scanf("%d", &afterValue);
            newNode->data = malloc(sizeof(int));
            *(int *)newNode->data = newValue;

            struct Node *temp = head;
            while (temp != NULL && (temp->dataType != 1 || *(int *)temp->data != afterValue)) {
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp->next;
            temp->next = newNode;
            printf("\nNode inserted after value.\n");
            displayListAfterOperation();
            break;
        }
        case 2: {
            float newValue, afterValue;
            printf("Enter value to insert: ");
            scanf("%f", &newValue);
            printf("Enter value after which to insert: ");
            scanf("%f", &afterValue);
            newNode->data = malloc(sizeof(float));
            *(float *)newNode->data = newValue;

            struct Node *temp = head;
            while (temp != NULL && (temp->dataType != 2 || *(float *)temp->data != afterValue)) {
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode ->next = temp->next;
            temp->next = newNode;
            printf("\nNode inserted after value.\n");
            displayListAfterOperation();
            break;
        }
        case 3: {
            char newValue, afterValue;
            printf("Enter value to insert: ");
            scanf("%c", &newValue);
            getchar();
            printf("Enter value after which to insert: ");
            scanf("%c", &afterValue);
            getchar();
            newNode->data = malloc(sizeof(char));
            *(char *)newNode->data = newValue;

            struct Node *temp = head;
            while (temp != NULL && (temp->dataType != 3 || *(char *)temp->data != afterValue)) {
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp->next;
            temp->next = newNode;
            printf("\nNode inserted after value.\n");
            displayListAfterOperation();
            break;
        }
        case 4: {
            char newValue[100], afterValue[100];
            printf("Enter value to insert: ");
            fgets(newValue, sizeof(newValue), stdin);
            newValue[strcspn(newValue, "\n")] = 0;
            printf("Enter value after which to insert: ");
            fgets(afterValue, sizeof(afterValue), stdin);
            afterValue[strcspn(afterValue, "\n")] = 0;
            newNode->data = malloc(strlen(newValue) + 1);
            strcpy((char *)newNode->data, newValue);

            struct Node *temp = head;
            while (temp != NULL && (temp->dataType != 4 || strcmp((char *)temp->data, afterValue) != 0)) {
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            newNode->next = temp->next;
            temp->next = newNode;
            printf("\nNode inserted after value.\n");
            displayListAfterOperation();
            break;
        }
    }
}

void deleteAtStart() {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;
    free(temp->data); // Free the data
    free(temp); // Free the node
    printf("\nNode deleted from the start.\n");
    displayListAfterOperation();
}

void deleteAtEnd() {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        free(head->data); // Free the data
        free(head); // Free the node
        head = NULL;
        printf("\nNode deleted from the end.\n");
        displayListAfterOperation();
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp->data); // Free the data
    free(temp); // Free the node
    printf("\nNode deleted from the end.\n");
    displayListAfterOperation();
}

void deleteByValue() {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    switch (currentDataType) {
        case 1: {
            int value;
            printf("Enter value to delete: ");
            scanf("%d", &value);

            if (head->dataType == 1 && *(int *)head->data == value) {
                deleteAtStart();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 1 || *(int *)temp->data != value)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            prev->next = temp->next;
            free(temp->data); // Free the data
            free(temp); // Free the node
            printf("\nNode deleted by value.\n");
            displayListAfterOperation();
            break;
        }
        case 2: {
            float value;
            printf("Enter value to delete: ");
            scanf("%f", &value);

            if (head->dataType == 2 && *(float *)head->data == value) {
                deleteAtStart();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 2 || *(float *)temp->data != value)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            prev->next = temp->next;
            free(temp->data); // Free the data
            free(temp); // Free the node
            printf("\nNode deleted by value.\n");
            displayListAfterOperation();
            break;
        }
        case 3: {
            char value;
            printf("Enter value to delete: ");
            scanf("%c", &value);
            getchar();

            if (head->dataType == 3 && *(char *)head->data == value) {
                deleteAtStart();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 3 || *(char *)temp->data != value)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            prev->next = temp->next;
            free(temp->data); // Free the data
            free(temp); // Free the node
            printf("\nNode deleted by value.\n");
            displayListAfterOperation();
            break;
        }
        case 4: {
            char value[100];
            printf("Enter value to delete: ");
            fgets(value, sizeof(value), stdin);
            value[strcspn(value, "\n")] = 0;

            if (head->dataType == 4 && strcmp((char *)head->data, value) == 0) {
                deleteAtStart();
                return;
            }

            struct Node *temp = head;
            struct Node *prev = NULL;
            while (temp != NULL && (temp->dataType != 4 || strcmp((char *)temp->data, value) != 0)) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("\nValue not found.\n");
                return;
            }

            prev->next = temp->next;
            free(temp->data); // Free the data
            free(temp); // Free the node
            printf("\nNode deleted by value.\n");
            displayListAfterOperation();
            break;
        }
    }
}

void emptyList() {
    clrscr();
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data); // Free the data
        free(temp); // Free the node
    }
    printf("\nList is now empty.\n");
    displayListAfterOperation();
}

int main() {
    int choice;

    do {
        clrscr();
#ifdef _WIN32
        gotoxy(30, 2); printf("<@@ SINGLY LINKED LIST AND OPERATORS @@>\n");
        gotoxy(10, 4); printf("1. CREATION OF LIST\n");
        gotoxy(10, 5); printf("2. TRAVERSAL OF LIST\n");
        gotoxy(10, 6); printf("3. INSERTION OF NODE AT THE START\n");
        gotoxy(10, 7); printf("4. INSERTION OF NODE AT THE END\n");
        gotoxy(10, 8); printf("5. INSERTION OF NODE BEFORE A VALUE\n");
        gotoxy(50, 4); printf("6. INSERTION OF NODE AFTER A VALUE\n");
        gotoxy(50, 5); printf("7. DELETION OF NODE AT THE START\n");
		gotoxy(50, 6); printf("8. DELETION OF NODE AT THE END\n");
        gotoxy(50, 7); printf("9. DELETION BY VALUE\n");
        gotoxy(50, 8); printf("10. EMPTY LIST\n");
        gotoxy(35, 10); printf("11. EXIT\n");
        gotoxy(30, 12); printf("Enter your choice: ");
#else
        printf("<@@ SINGLY LINKED LIST AND OPERATORS @@>\n\n");
        printf("1. CREATION OF LIST\n");
        printf("2. TRAVERSAL OF LIST\n");
        printf("3. INSERTION OF NODE AT THE START\n");
        printf("4. INSERTION OF NODE AT THE END\n");
        printf("5. INSERTION OF NODE BEFORE A VALUE\n");
        printf("6. INSERTION OF NODE AFTER A VALUE\n");
        printf("7. DELETION OF NODE AT THE START\n");
        printf("8. DELETION OF NODE AT THE END\n");
        printf("9. DELETION BY VALUE\n");
        printf("10. EMPTY LIST\n");
        printf("11. EXIT\n");
        printf("Enter your choice: ");
#endif
        scanf("%d", &choice);
        getchar();

        if (choice >= 2 && choice <= 10 && !listCreated && choice != 1) {
            printf("List must be created first.\n");
            printf("Press Enter to continue...");
            getchar();
            continue;
        }

        switch (choice) {
            case 1:
                createList();
                break;
            case 2:
                traverseList();
                break;
            case 3:
                insertAtStart();
                break;
            case 4:
                insertAtEnd();
                break;
            case 5:
                insertBeforeValue();
                break;
            case 6:
                insertAfterValue();
                break;
            case 7:
                deleteAtStart();
                break;
            case 8:
                deleteAtEnd();
                break;
            case 9:
                deleteByValue();
                break;
            case 10:
                emptyList();
                break;
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
        if (choice != 11) {
            printf("Press Enter to continue...");
            getchar();
        }

    } while (choice != 11);

    return 0;
}