// SCRAPED DUE TO THE COMPLEXITY.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCTURE DECLARATION: /////////////////////////////////////////////////////////////////////////////////////

// Defines the "node" structure, which represents a list element. 
// This structure is used to store data and link nodes during runtime.
typedef struct node
{
    char **field; // A pointer to an array of strings (each element is a char pointer)
    struct node *next;

} node;

// Defines the "list" structure, which represents a linked list
// This structure holds metadata about the list and a pointer to its first node.
typedef struct list
{
    char name[50]; // Name of the entire list
    char **fieldNames; // Array to store field names
    int *fieldTypes; // Array to store field types (1 = int, 2 = float, 3 = char, 4 = string)
    int fieldCount; // Number of fields
    node *start;

} list;

list *currentList = NULL; // Global list pointer

// FUNCTIONS DECLARATION: ////////////////////////////////////////////////////////////////////////////////////

// Menu Functions
int menuChoice(); // Gets User Input and Returns it.
void menuClearConsole(); // Waits for the user to send any input to continue the program
void menuPauseConsole(); // Clear the console on Windows, Linux and MacOS
void menuDisplayList();

// General Functions
/* Validate if a string represents a valid integer or float.
        @param input        The string to validate.
        @param allowFloat   If 1 (true), allows float numbers.
                            If 0 (false), only integer numbers are allowed.
 
        @return             1 if valid, 0 if invalid.
*/
int isValidNumber(char *input, int allowFloat);
/* Function to safely read user input and remove the newline character
        @param buffer       The character array to store the input
        @param size         The maximum size of the input buffer
*/
void readInput(char *buffer, int size);
node* createAndFillNode();
int isListEmpty(node* temp);
int isListAvailable();
void freeNode(node* target);

// Single Linked List Operations Functions
node* createNode(); 
void createList(); // CREATION OF LIST
void displayNode(); // TRAVERSAL OF LIST VIA DISPLAY
int searchNode(); // TRAVERSAL OF LIST VIA SEARCH
node* selectNodeByField(); 
void insertAtStart(); // INSERTION OF NODE AT THE START
void insertAtEnd(); // INSERTION OF NODE AT THE END
void insertBeforeValue(); // INSERTION OF NODE BEFORE A VALUE
void insertAfterValue(); // INSERTION OF NODE AFTER A VALUE
void deleteAtStart(); // DELETION OF NODE AT THE START
void deleteAtEnd(); // DELETION OF NODE AT THE END
void deleteByValue();// DELETION OF NODE BY VALUE
void emptyLinkedList();// EMPTY LINKED LIST

// MAIN FUNCTION: ///////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    while (1) {
        menuClearConsole();
        
        // Main Menu Screen
        menuDisplayList();
        printf("\nMain Menu:\n");
        printf(
            "[1]. CREATION OF LIST AND NODE\n"
            "[2]. TRAVERSAL OF LIST\n"
            "[3]. INSERTION OF NODE AT THE START\n"
            "[4]. INSERTION OF NODE AT THE END\n"
            "[5]. INSERTION OF NODE BEFORE A VALUE\n"
            "[6]. INSERTION OF NODE AFTER A VALUE\n"
            "[7]. DELETION OF NODE AT THE START\n"
            "[8]. DELETION OF NODE AT THE END\n"
            "[9]. DELETION OF NODE BY VALUE\n"
            "[10]. EMPTY LINKED LIST\n"
            "[11]. EXIT THE PROGRAM\n");

        // Calling "menuChoice()" and expects a return value for "MainChoice" through User Input.
        int mainChoice = menuChoice();
        
        // Validation for "mainChoice" if its within the range of the main menu.
        if (mainChoice > 11 && mainChoice < 1){
            printf("Invalid Choice!");
            continue;
        }
        else {
            switch (mainChoice) // Executing functions based on User Input
            {
            case 1: // CREATION OF LIST
                menuClearConsole();
                createList();
                menuPauseConsole();
                break;

            case 2: // TRAVERSAL OF LIST
                menuClearConsole();
                while (1) {
                    menuClearConsole();
                    printf(
                        "Traversal of List:"
                        "\n[1]. SEARCH VALUE IN SELECTED FIELD"
                        "\n[2]. DISPLAY ALL NODES"
                        "\n[3]. RETURN TO MAIN MENU\n");
                    int subChoice = menuChoice();
                    if (subChoice == 3) break;
                    switch (subChoice) {
                        case 1: {
                            node** matchedNodes = NULL;
                            int matchCount = 0;
                            
                            // Call searchNode and store results
                            if (searchNode(&matchedNodes, &matchCount) > 0) {
                                printf("Search completed. %d results found.\n", matchCount);
                            }
                            
                            // Free allocated memory after displaying results
                            if (matchedNodes != NULL) {
                                free(matchedNodes);
                            }
                            
                            break;
                        }
                        case 2: displayNode(); break;
                        default: menuClearConsole(); printf("ERROR: Invalid choice.\n"); menuPauseConsole();
                    }
                }
                break;
                menuPauseConsole();
                break;

            case 3: // INSERTION OF NODE AT THE START
                menuClearConsole();
                insertAtStart();
                menuPauseConsole();
                break;

            case 4: // INSERTION OF NODE AT THE END
                menuClearConsole();
                insertAtEnd();
                menuPauseConsole();
                break;

            case 5: // INSERTION OF NODE BEFORE A VALUE
                menuClearConsole();
                insertBeforeValue();
                menuPauseConsole();
                break;

            case 6: // INSERTION OF NODE AFTER A VALUE
                menuClearConsole();
                insertAfterValue();
                menuPauseConsole();
                break;

            case 7: // DELETION OF NODE AT THE START
                menuClearConsole();
                deleteAtStart();
                menuPauseConsole();
                break;

            case 8: // DELETION OF NODE AT THE END
                menuClearConsole();
                deleteAtEnd();
                menuPauseConsole();
                break;

            case 9: // DELETION OF NODE BY VALUE
                menuClearConsole();
                deleteByValue();
                menuPauseConsole();
                break;

            case 10: // EMPTY LINKED LIST
                menuClearConsole();
                
                menuPauseConsole();
                break;

            case 11: // EXIT THE PROGRAM
                return 0;
            
            default: // NONE OF THE ABOVE!
                menuClearConsole();
                menuPauseConsole();
                break;
            }
        }
    }
}

// FUNCATIONS DEFINITION: ///////////////////////////////////////////////////////////////////////////////////////

// MENU FUNCTIONS: //
// Menu Choice Function: Gets User Input and Returns it.
int menuChoice(){
    int choice;

    printf("\nChoice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    return choice;
}

// Menu Pause Console Function: Waits for the user to send any input to continue the program
void menuPauseConsole() {
    printf("\nPress Enter to continue...");
    getchar();
}

// Menu Clear Console Function: Clear the console on Windows, Linux and MacOS
void menuClearConsole(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// 
void menuDisplayList() {
    if (currentList == NULL) {
        printf(
            "Welcome to \"Single Linked List Generator\"\n"
            "This Program allows the user to dynamically create their own custom list with custom nodes and fields!\n\n"
            "INFO: No list has been created yet.\n"
            "INFO: Please select \"[1] CREATION OF LIST AND NODE\" to create your very own custom list.\n");
        return;
    }

    printf("\nList Name: %s\n", currentList->name);
    
    for (int i = 0; i < currentList->fieldCount; i++) {
        // Convert field type to string
        char *type;
        switch (currentList->fieldTypes[i]) {
            case 1: type = "Integer"; break;
            case 2: type = "Float"; break;
            case 3: type = "Character"; break;
            case 4: type = "String"; break;
            default: type = "Unknown"; break;
        }

        // Display formatted field details
        printf(" - <%s> %s\n", type, currentList->fieldNames[i]);
    }
}

// GENERAL FUNCTIONS: //
// isValidNumber Function: Validate if a string is a valid integer or float
int isValidNumber(char *input, int allowFloat) {
    int i = 0;
    int dotCount = 0;

    // Check for negative sign at the start
    if (input[0] == '-') {  
        i = 1;
        if (input[1] == '\0') return 0; // "-" alone is invalid
    }

    // Iterate through each character in the string
    for (; input[i] != '\0'; i++) {
        if (input[i] == '.') {
            // If float is not allowed or more than one dot appears, return invalid
            if (!allowFloat || ++dotCount > 1) return 0;
        } 
        // If character is not a digit, return invalid
        else if (!isdigit(input[i])) return 0;
    }

    return 1; // String is a valid number
}

// 
void readInput(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
}

// 
node* createNode(list *list) {
    
    /* Documentation 
    
    [1] newNode stores the memory address of the newly allocated node structure.
    
    [2] (node*) casts the void* returned by malloc() to node* 
        (a pointer to a node structure). 
        - This is necessary in C++ but optional in C.

    [3] malloc(sizeof(node)) allocates memory for a node structure 
        on the heap, ensuring it persists beyond the function scope.

    Example: 
    Let's assume malloc(sizeof(node)) returns 0x100 (some memory address).
    Then, newNode stores 0x100 (newNode = 0x100).
    
    At memory address 0x100, space is allocated for:
    
        [ data | next ]
    
    - data (an integer or any other field in the node) is uninitialized.
    - next (a pointer to another node) is also uninitialized 
      until explicitly set (e.g., newNode->next = NULL).
    */
    node *newNode = (node*)malloc(sizeof(node));
    
    // Validate memory allocation before accessing newNode
    if (!newNode){
        printf("ERROR: Memory allocation failed.\n");
        menuPauseConsole();
        exit(1);
    }

    // Allocate memory for 'field' (array of pointers)
    newNode->field = (char**)malloc(sizeof(char*) * list->fieldCount);
    if (!newNode->field) {
        printf("ERROR: Memory allocation failed.\n");
        free(newNode);
        menuPauseConsole();
        exit(1);
    }

    // Allocate memory for each field string (array of characters)
    for (int i = 0; i < list->fieldCount; i++) {
        newNode->field[i] = (char*)malloc(sizeof(char) * 100);
        if (!newNode->field[i]) {
            printf("ERROR: Memory allocation failed.\n");

            // Free all previously allocated fields
            for (int j = 0; j < i; j++) {
                free(newNode->field[j]);
            }
            free(newNode->field); // Free the field array
            free(newNode); // Free the node structure

            menuPauseConsole();
            exit(1);
        }
    }
   
    newNode->next = NULL; // Initialize the next pointer to NULL to avoid accessing an uninitialized pointer
    return newNode; 
}

//
int isListAvailable() {
    if (currentList == NULL) {
        printf(
            "ERROR: No list has been created yet.\n"
            "INFO: Please select \"[1] CREATION OF LIST AND NODE\" to create your very own custom list.\n");
        return 0; // List is unavailable
    }
    return 1; // List is available
}

//
node* createAndFillNode() {
    node* newNode = createNode(currentList);
    for (int i = 0; i < currentList->fieldCount; i++) {
        while (1) {
            printf("Enter %s: ", currentList->fieldNames[i]);
            readInput(newNode->field[i], 100);

            if (currentList->fieldTypes[i] == 1) { // Integer validation
                if (!isValidNumber(newNode->field[i], 0)) {
                    printf("ERROR: Invalid integer. Please enter a valid number.\n");
                    continue;
                }
            } else if (currentList->fieldTypes[i] == 2) { // Float validation
                if (!isValidNumber(newNode->field[i], 1)) {
                    printf("ERROR: Invalid float. Please enter a valid number.\n");
                    continue;
                }
            } else if (currentList->fieldTypes[i] == 3) { // Character validation
                if (strlen(newNode->field[i]) != 1) {
                    printf("ERROR: Invalid character. Please enter a single character.\n");
                    continue;
                }
            }

            if (newNode->field[i][0] != '\0') break;
            printf("Input cannot be empty. Please try again.\n");
        }
    }
    return newNode;
}

//
void freeNode(node* target) {
    if (target == NULL) return;
    if (currentList == NULL) return; // Ensure currentList exists before accessing fieldCount

    // Free each allocated field (only if target->field exists)
    if (target->field != NULL) {
        for (int i = 0; i < currentList->fieldCount; i++) {
            if (target->field[i] != NULL) { // Ensure field[i] exists before freeing
                free(target->field[i]);
            }
        }
        free(target->field); // Free the array of field pointers
    }

    free(target); // Free the node itself
}

// 
void createList() {
    // Prevent creating multiple lists
    if (currentList != NULL) {
        printf("ERROR: A list has already been created.\n");
        return;
    }

    // Allocate memory for the list
    currentList = (list*)malloc(sizeof(list));
    if (!currentList) {
        printf("ERROR: Memory allocation failed for the list.\n");
        return;
    }

    currentList->start = NULL;
    currentList->fieldCount = 0;
    
    // Get the list name
    printf("Enter the name of the list: ");
    readInput(currentList->name, 50);

    currentList->fieldNames = NULL;
    currentList->fieldTypes = NULL;
    
    // Initialize field properties
    int fieldChoice;
    char fieldName[50];

    // Input fields
    while (1) {
        printf("\nSelect field type:\n");
        printf(
            "[1]. Integer\n"
            "[2]. Float\n"
            "[3]. Character\n"
            "[4]. String\n"
            "[5]. Finish\n\n");

        fieldChoice = menuChoice();
        
        if (fieldChoice == 5) {
            if (currentList->fieldCount == 0) {
                printf("\nERROR: You must add at least one field before finishing.\n");
                continue;
            }
            break;
        }

        if (fieldChoice < 1 || fieldChoice > 4) {
            printf("\nERROR: Invalid choice. Try again.\n");
            continue;
        }

        printf("\nEnter field name: ");
        readInput(fieldName, 50);

        currentList->fieldCount++;
        
        // Safely reallocate memory for fieldNames and fieldTypes
        char** tempFieldNames = (char**)realloc(currentList->fieldNames, sizeof(char*) * currentList->fieldCount);
        int* tempFieldTypes = (int*)realloc(currentList->fieldTypes, sizeof(int) * currentList->fieldCount);

        if (!tempFieldNames || !tempFieldTypes) {
            printf("ERROR: Memory allocation failed.\n");
            
            // Free previously allocated field names
            for (int i = 0; i < currentList->fieldCount - 1; i++) {
                free(currentList->fieldNames[i]);
            }

            free(currentList->fieldNames);
            free(currentList->fieldTypes);
            free(currentList);
            return;
        }

        currentList->fieldNames = tempFieldNames;
        currentList->fieldTypes = tempFieldTypes;

        // Allocate and Copy Field Name
        currentList->fieldNames[currentList->fieldCount - 1] = (char*)malloc(strlen(fieldName) + 1);
        if (!currentList->fieldNames[currentList->fieldCount - 1]) {
            printf("ERROR: Memory allocation failed for field name.\n");
            continue;
        }
        strcpy(currentList->fieldNames[currentList->fieldCount - 1], fieldName);
        currentList->fieldTypes[currentList->fieldCount - 1] = fieldChoice;
    }

    printf("\nINFO: List '%s' created successfully with %d fields.\n", currentList->name, currentList->fieldCount);
    menuDisplayList();
}

// Function to display all nodes
void displayNode() {
    if (currentList == NULL || currentList->start == NULL) {
        menuClearConsole();
        printf(
            "\nERROR: No list or nodes available.\n"
            "INFO: Please select \"[1] CREATION OF LIST AND NODE\" to create your very own custom list.\n"
            "INFO: If a list has been created, please create your first Node.\n");
        menuPauseConsole();
        return;
    }
    
    menuClearConsole();
    printf("\n%s:\n", currentList->name);
    node *temp = currentList->start;
    
    while (temp) {
        for (int i = 0; i < currentList->fieldCount; i++) {
            printf("%s: %s  |  ", currentList->fieldNames[i], temp->field[i]);
        }
        printf("\n");
        temp = temp->next;
    }
    
    menuPauseConsole();
    menuClearConsole();
}

// ❗❗❗ Function to search for a node by field
int searchNode(node*** matchedNodes, int* matchCount) {
    if (currentList == NULL || currentList->start == NULL) {
        printf("\nERROR: No list or nodes available.\n"
               "INFO: Please create a list and at least one node first.\n");
        menuPauseConsole();
        return 0;
    }

    menuClearConsole();
    printf("Select the field to search on:\n");
    for (int i = 0; i < currentList->fieldCount; i++) {
        printf("[%d] %s\n", i + 1, currentList->fieldNames[i]);
    }

    int fieldChoice = menuChoice();
    if (fieldChoice < 1 || fieldChoice > currentList->fieldCount) {
        printf("Invalid field choice.\n");
        menuPauseConsole();
        return 0;
    }
    int fieldIndex = fieldChoice - 1;

    char searchValue[100];
    printf("Enter the value to search for in %s: ", currentList->fieldNames[fieldIndex]);
    readInput(searchValue, 100);

    // Count total nodes
    int totalNodes = 0;
    node* temp = currentList->start;
    while (temp) {
        totalNodes++;
        temp = temp->next;
    }

    // Allocate space for matched nodes
    *matchedNodes = malloc(sizeof(node*) * totalNodes);
    *matchCount = 0;
    temp = currentList->start;
    
    while (temp) {
        if (strcmp(temp->field[fieldIndex], searchValue) == 0) {
            (*matchedNodes)[(*matchCount)++] = temp;
        }
        temp = temp->next;
    }

    if (*matchCount == 0) {
        printf("No matching nodes found for %s = %s\n", currentList->fieldNames[fieldIndex], searchValue);
        free(*matchedNodes);
        *matchedNodes = NULL;
        menuPauseConsole();
        return 0;
    }

    // Display results
    if (*matchCount == 1) {
        printf("Matched! There is 1 result:\n");
    } else {
        printf("Matched! There are %d results:\n", *matchCount);
    }
    
    for (int i = 0; i < *matchCount; i++) {
        printf("[%d] %s: %s\n", i + 1, currentList->fieldNames[fieldIndex], (*matchedNodes)[i]->field[fieldIndex]);
    }

    menuPauseConsole();
    return *matchCount;
}

//
node* selectNodeByField() {
    node** matchedNodes = NULL;
    int matchCount = 0;

    // Use searchNode to get matched results
    if (searchNode(&matchedNodes, &matchCount) == 0) {
        return NULL;
    }

    node* selectedNode = NULL;
    if (matchCount == 1) {
        selectedNode = matchedNodes[0];
        printf("Automatically selecting the only match.\n");
    } else {
        printf("Select a match (1-%d): ", matchCount);
        int selectedIndex = menuChoice() - 1;
        if (selectedIndex < 0 || selectedIndex >= matchCount) {
            printf("Invalid selection.\n");
            free(matchedNodes);
            menuPauseConsole();
            return NULL;
        }
        selectedNode = matchedNodes[selectedIndex];
    }

    free(matchedNodes);
    return selectedNode;
}

// SINGLE LINKED LIST OPERATION FUNCTIONS: //
// ✅✅✅
void insertAtStart() {
    if (!isListAvailable()) return;

    node* newNode = createAndFillNode();

    // If list is empty, set the new node as start
    if (currentList->start == NULL) {
        currentList->start = newNode;
    } 
    else {    
    // Insert newNode at the start of the list
    newNode->next = currentList->start;
    currentList->start = newNode;
    }
    printf("Node successfully inserted at the start.\n");
}

// ✅✅✅
void insertAtEnd () {
    if (!isListAvailable()) return;

    node* newNode = createAndFillNode();
    if (!newNode) {  // Check for memory allocation failure
        printf("ERROR: Memory allocation for new node failed.\n");
        return;
    }

    newNode->next = NULL;

    // If the list is empty, make the new node the first node
    if (currentList->start == NULL) {
        currentList->start = newNode;
    } else {
        // Traverse to the last node and insert newNode
        node* end = currentList->start;
        while (end->next != NULL) {
            end = end->next;
        }
        end->next = newNode;
    }

    printf("Node successfully inserted at the end.\n");
}

// ❗❗❗
void insertBeforeValue() {
    if (!isListAvailable()) return;

    printf("Insert node before the selected node.\n");
    node* target = selectNodeByField();
    if (target == NULL) return;

    node* newNode = createAndFillNode();

    node* previous = NULL;
    node* temp = currentList->start;
    while (temp && temp != target) {
        previous = temp;
        temp = temp->next;
    }

    newNode->next = target;
    if (previous == NULL) {
        currentList->start = newNode;
    } else {
        previous->next = newNode;
    }

    printf("Node successfully inserted before the selected node.\n");
}

// ❗❗❗
void insertAfterValue() {
    if (!isListAvailable()) return;

    printf("Insert node after the selected node.\n");
    node* target = selectNodeByField();
    if (target == NULL) return;

    node* newNode = createAndFillNode();
    newNode->next = target->next;
    target->next = newNode;

    printf("Node successfully inserted after the selected node.\n");
}

// ✅✅✅
void deleteAtStart() {
    if (!isListAvailable()) return;

    node *delNode = currentList->start;

    if (delNode == NULL) {
        printf("List is already empty.\n");
        return;
    }

    currentList->start = currentList->start->next;
    freeNode(delNode);

    printf("Node deleted from the start.\n");
}


// ✅✅✅
void deleteAtEnd() {
    if (!isListAvailable()) return;

    node* delNode = currentList->start;  
    node* previous = NULL;

    if (delNode == NULL) {
        printf("List is already empty.\n");
        return;
    }

    while (delNode->next != NULL) {
        previous = delNode;
        delNode = delNode->next;
    }

    if (previous == NULL) { // If there is only one node
        freeNode(currentList->start);
        currentList->start = NULL;
    } else {
        previous->next = NULL;
        freeNode(delNode);
    }

    printf("Last node has been successfully deleted.\n");
}

// ❗❗❗
void deleteByValue() {
    if (!isListAvailable()) return;

    printf("Delete the selected node.\n");
    node* target = selectNodeByField();
    if (target == NULL) return;

    node* previous = NULL;
    node* temp = currentList->start;
    while (temp && temp != target) {
        previous = temp;
        temp = temp->next;
    }

    if (previous == NULL) {
        currentList->start = target->next;
    } else {
        previous->next = target->next;
    }

    for (int i = 0; i < currentList->fieldCount; i++) {
        free(target->field[i]);
    }
    free(target->field);
    free(target);

    printf("Selected node deleted successfully.\n");
}