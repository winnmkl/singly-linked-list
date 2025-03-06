#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#define clrscr() system("cls")
#else
#define clrscr() printf("\033[H\033[J")
#endif

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void displayListAfterOperation() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    printf("Current List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void createList() {
    clrscr();
    int n, value, i;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        return;
    }

    head = (struct Node *)malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter data for node 1: ");
    scanf("%d", &head->data);
    head->next = NULL;

    struct Node *temp = head;
    i = 2;
    while (i <= n) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        printf("Enter data for node %d: ", i);
        scanf("%d", &newNode->data);
        newNode->next = NULL;
        temp->next = newNode;
        temp = newNode;
        i++;
    }
    printf("List created.\n");
    displayListAfterOperation();
}

void traverseList() {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    printf("List elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void insertAtStart(int value) {
    clrscr();
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    printf("Node inserted at the start.\n");
    displayListAfterOperation();
}

void insertAtEnd(int value) {
    clrscr();
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        printf("Node inserted at the end.\n");
        displayListAfterOperation();
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Node inserted at the end.\n");
    displayListAfterOperation();
}

void insertBeforeValue(int value, int newValue) {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->data == value) {
        insertAtStart(newValue);
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = newValue;
    newNode->next = temp;
    prev->next = newNode;
    printf("Node inserted before value.\n");
    displayListAfterOperation();
}

void insertAfterValue(int value, int newValue) {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = newValue;
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Node inserted after value.\n");
    displayListAfterOperation();
}

void deleteAtStart() {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;
    free(temp);
    printf("Node deleted from the start.\n");
    displayListAfterOperation();
}

void deleteAtEnd() {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        printf("Node deleted from the end.\n");
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
    free(temp);
    printf("Node deleted from the end.\n");
    displayListAfterOperation();
}

void deleteByValue(int value) {
    clrscr();
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->data == value) {
        deleteAtStart();
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Node deleted by value.\n");
    displayListAfterOperation();
}

void emptyList() {
    clrscr();
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("List is now empty.\n");
    displayListAfterOperation();
}

int main() {
    int choice, value, newValue, beforeValue, afterValue;

    do {
        clrscr();
        printf("Menu:\n");
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
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createList();
                break;
            case 2:
                traverseList();
                break;
            case 3:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtStart(value);
                break;
            case 4:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;
            case 5:
                printf("Enter value to insert: ");
                scanf("%d", &newValue);
                printf("Enter value before which to insert: ");
                scanf("%d", &beforeValue);
                insertBeforeValue(beforeValue, newValue);
                break;
            case 6:
                printf("Enter value to insert: ");
                scanf("%d", &newValue);
                printf("Enter value after which to insert: ");
                scanf("%d", &afterValue);
                insertAfterValue(afterValue, newValue);
                break;
            case 7:
                deleteAtStart();
                break;
            case 8:
                deleteAtEnd();
                break;
            case 9:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(value);
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
        if(choice != 11){
            printf("Press Enter to continue...");
            getchar();
            getchar();
        }

    } while (choice != 11);

    return 0;
}