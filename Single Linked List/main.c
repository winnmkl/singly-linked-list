#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// CREATION OF LIST
// TRAVERSAL OF LIST
// INSERTION OF NODE AT THE START
// INSERTION OF NODE AT THE END
// INSERTION OF NODE BEFORE A VALUE
// INSERTION OF NODE AFTER A VALUE
// DELETION OF NODE AT THE START
// DELETION OF NODE AT THE END
// DELETION OF NODE BY VALUE
// EMPTY LINKED LIST
////////////////////////////////////////////////////////////

// Structure for a Node (each node contains field fields and a pointer to the next node)
typedef struct Node {
    char **field;   // Array of strings to store field values
    struct Node *next; // Pointer to the next node
} Node;

// Structure for a List (contains the name and node structure)
typedef struct List {
    char name[50]; // Name of the list
    char **fieldNames; // Array to store field names
    int *fieldTypes; // Array to store field types (1 = int, 2 = float, 3 = char, 4 = string)
    int fieldCount; // Number of fields
    Node *start; // Pointer to the first node
} List;

List *currentList = NULL; // Global list pointer

// Function to read a full line input
void readInput(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
}

// Function to validate integer input
int isValidInteger(char *input) {
    int i = 0;

    if (input[0] == '-') {  
        i = 1;
        if (input[1] == '\0') return 0;
    }

    for (; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) return 0;
    }
    return 1;
}


// Function to validate float input
int isValidFloat(char *input) {
    int dotCount = 0;
    int i = 0;

    if (input[0] == '-') {  
        i = 1;
        if (input[1] == '\0') return 0;
    }

    for (; input[i] != '\0'; i++) {
        if (input[i] == '.') {
            dotCount++;
            if (dotCount > 1) return 0;
        } else if (!isdigit(input[i])) return 0;
    }
    return 1;
}


// Function to create a new node
Node* createNode(List *list) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->field = (char**)malloc(sizeof(char*) * list->fieldCount);
    if (!newNode->field) {
        printf("Memory allocation failed.\n");
        free(newNode);
        exit(1);
    }

    for (int i = 0; i < list->fieldCount; i++) {
        newNode->field[i] = (char*)malloc(sizeof(char) * 100);
        if (!newNode->field[i]) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the start
void insertAtStart() {
    if (currentList == NULL) {
        printf("No list has been created yet.\n");
        return;
    }
    
    Node *newNode = createNode(currentList);
    for (int i = 0; i < currentList->fieldCount; i++) {
        while (1) {
            printf("Enter %s: ", currentList->fieldNames[i]);
            readInput(newNode->field[i], 100);
            
            if (currentList->fieldTypes[i] == 1 && !isValidInteger(newNode->field[i])) {
                printf("Invalid input. Please enter an integer.\n");
            } else if (currentList->fieldTypes[i] == 2 && !isValidFloat(newNode->field[i])) {
                printf("Invalid input. Please enter a float.\n");
            } else if (currentList->fieldTypes[i] == 3 && strlen(newNode->field[i]) != 1) {
                printf("Invalid input. Please enter a single character.\n");
            } else {
                break;
            }
        }
    }
    
    newNode->next = currentList->start;
    currentList->start = newNode;
    printf("Node has been successfully added.\n");
}

// Function to display all nodes
void displayNodes() {
    if (currentList == NULL || currentList->start == NULL) {
        printf("No list or nodes available.\n");
        return;
    }
    
    printf("\n%s:\n", currentList->name);
    Node *temp = currentList->start;
    while (temp) {
        for (int i = 0; i < currentList->fieldCount; i++) {
            printf("%s: %s  |  ", currentList->fieldNames[i], temp->field[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}

// Function to search for a node by field
void searchNode() {
    if (currentList == NULL || currentList->start == NULL) {
        printf("No list or nodes available.\n");
        return;
    }
    
    printf("\nWhat type of field would you like to search?\n");
    for (int i = 0; i < currentList->fieldCount; i++) {
        printf("%d. %s\n", i + 1, currentList->fieldNames[i]);
    }
    
    int choice;
    printf("Choice: ");
    scanf("%d", &choice);
    getchar(); // Clear newline character
    
    if (choice < 1 || choice > currentList->fieldCount) {
        printf("Invalid choice.\n");
        return;
    }
    
    char searchValue[100];
    printf("Enter value to search: ");
    readInput(searchValue, 100);
    if (strlen(searchValue) == 0) {
        printf("Search value cannot be empty.\n");
        return;
    }
    
    Node *temp = currentList->start;
    int found = 0;
    while (temp) {
        if (strcmp(temp->field[choice - 1], searchValue) == 0) {
            found = 1;
            printf("Match found:\n");
            for (int i = 0; i < currentList->fieldCount; i++) {
                printf("%s: %s  |  ", currentList->fieldNames[i], temp->field[i]);
            }
            printf("\n");
        }
        temp = temp->next;
    }
    
    if (!found) {
        printf("No matching field found.\n");
    }
}

// Function to create a list
void createList() {
    if (currentList != NULL) {
        printf("A list has already been created.\n");
        return;
    }
    
    currentList = (List*)malloc(sizeof(List));
    currentList->start = NULL;
    
    printf("Enter the name of the list: ");
    readInput(currentList->name, 50);
    
    int fieldChoice;
    char fieldName[50];
    currentList->fieldNames = (char**)malloc(sizeof(char*) * 100);
    currentList->fieldTypes = (int*)malloc(sizeof(int) * 100);
    currentList->fieldCount = 0;
    
    while (1) {
        printf("\nSelect field type:\n");
        printf("1. Integer\n2. Float\n3. Character\n4. String\n5. Finish\n");
        printf("Choice: ");
        scanf("%d", &fieldChoice);
        getchar(); // Clear newline character
        
        if (fieldChoice == 5) break;
        
        printf("Enter field name: ");
        readInput(fieldName, 50);
        
        currentList->fieldNames[currentList->fieldCount] = (char*)malloc(strlen(fieldName) + 1);
        strcpy(currentList->fieldNames[currentList->fieldCount], fieldName);
        currentList->fieldTypes[currentList->fieldCount] = fieldChoice;
        currentList->fieldCount++;
    }
    
    printf("List '%s' has been created successfully.\n", currentList->name);
}

int main() {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. CREATION OF LIST\n2. TRAVERSAL OF LIST\n3. INSERTION OF NODE AT THE START\n11. EXIT\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: 
                createList(); 
                break;
            case 2: {
                int subChoice;
                while (1) {
                    printf("\n1. Search Value of Field in Nodes\n2. Display All Nodes\n3. Back\nChoice: ");
                    scanf("%d", &subChoice);
                    getchar();

                    if (subChoice == 3) break;

                    switch (subChoice) {
                        case 1: searchNode(); break;
                        case 2: displayNodes(); break;
                        default: printf("Invalid choice.\n");
                    }
                }
                break;
            }
            case 3: 
                insertAtStart(); 
                break;
            case 11: 
                return 0;
            default: 
                printf("Invalid choice.\n");
        }
    }
}