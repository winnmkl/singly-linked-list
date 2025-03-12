/**
 * @file main.c
 * @brief Implementation of a dynamic doubly linked list with user-defined fields.
 * 
 * This program allows users to create and manage a doubly linked list with 
 * custom fields and field types. Users can insert, delete, search, and display nodes dynamically.
 * 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 
 // STRUCTURE DECLARATION: /////////////////////////////////////////////////////////////////////////////////////
 
 /**
  * @struct node
  * @brief Represents an individual node in the doubly linked list.
  */
 typedef struct node
 {
     char **field; /**< Pointer to an array of field values (strings). */
     struct node *next; /**< Pointer to the next node. */
     struct node *prev; /**< Pointer to the previous node. */
 
 } node;
 
 /**
  * @struct list
  * @brief Represents a doubly linked list with metadata.
  */
 typedef struct list
 {
     char name[50]; /**< Name of the list. */
     char **fieldNames; /**< Array of field names. */
     int *fieldTypes; /**< Array of field types (1=int, 2=float, 3=char, 4=string). */
     int fieldCount; /**< Number of fields. */
     node *start; /**< Pointer to the first node in the list. */
     node *end; /**< Pointer to the last node in the list. */
 
 } list;
 
 list *currentList = NULL;
 
 // FUNCTIONS DECLARATION: //////////////////////////////////////////////////////////
 
 // 1. MENU FUNCTIONS //
 int menuChoice();          // Gets user input and returns it
 void menuClearConsole();   // Clears the console (Windows, Linux, MacOS)
 void menuPauseConsole();   // Waits for user input before continuing
 void menuDisplayList();    // Displays the current list
 
 // 2. GENERAL UTILITY FUNCTIONS //
 int isValidNumber(char *input, int allowFloat);             // Validates if a string is a valid number
 void readInput(char *buffer, int size);                     // Reads user input safely
 node* createAndFillNode();                                  // Creates and fills a new node
 int isListEmpty(node* temp);                                // Checks if a given list is empty
 int isListAvailable(int checkNodes, int suppressWarnings);  // Checks if a list exists before operations
 void freeNode(node* target);                                // Frees memory allocated for a node
 
 // 3. LINKED LIST MANAGEMENT //
 node* createNode();      // Creates a new node with allocated memory
 void createList();       // Creates a new list structure
 void emptyLinkedList();  // Deletes all nodes in the linked list
 
 // 4. LINKED LIST TRAVERSAL FUNCTIONS //
 void displayNode();                                     // Displays all nodes in the list
 int searchNode(node*** matchedNodes, int* matchCount);  // Searches for a node by field value
 node* selectNodeByField();                              // Allows user to select a node by searching
 
 // 5. LINKED LIST MODIFICATION FUNCTIONS //
 void insertAtStartOrEnd(int insertAtStart);  // Inserts a node at the start or end
 void insertBeforeOrAfter(int insertBefore);  // Inserts a node before or after a given value
 void deleteAtStartOrEnd(int deleteAtStart);  // Deletes a node at the start or end
 void deleteByValue();                        // Deletes a node by value
 void emptyList();
 
 
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
 
         // Get user choice
         int mainChoice = menuChoice(1, 11);
 
         switch (mainChoice) { // Execute functions based on User Input
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
                         "Traversal of List:\n"
                         "[1]. SEARCH VALUE IN SELECTED FIELD\n"
                         "[2]. DISPLAY ALL NODES\n"
                         "[3]. RETURN TO MAIN MENU\n");
 
                     int subChoice = menuChoice(1, 3); // Ensures valid input (1-3)
                     if (subChoice == 3) break;
 
                     switch (subChoice) {
                         case 1: {
                             node** matchedNodes = NULL;
                             int matchCount = 0;
                             menuClearConsole();
                             searchNode(&matchedNodes, &matchCount);
                             menuPauseConsole();
                             break;
                         }
                         case 2:
                             displayNode();
                             break;   
                         default:
                             menuClearConsole();
                             printf("ERROR: Invalid choice.\n");
                             menuPauseConsole();
                     }
                 }
                 break;
 
             case 3: // INSERTION OF NODE AT THE START
                 menuClearConsole();
                 insertAtStartOrEnd(1);
                 menuPauseConsole();
                 break;
 
             case 4: // INSERTION OF NODE AT THE END
                 menuClearConsole();
                 insertAtStartOrEnd(0);
                 menuPauseConsole();
                 break;
 
             case 5: // INSERTION OF NODE BEFORE A VALUE
                 menuClearConsole();
                 insertBeforeOrAfter(1);
                 menuPauseConsole();
                 break;
 
             case 6: // INSERTION OF NODE AFTER A VALUE
                 menuClearConsole();
                 insertBeforeOrAfter(0);
                 menuPauseConsole();
                 break;
 
             case 7: // DELETION OF NODE AT THE START
                 menuClearConsole();
                 deleteAtStartOrEnd(1);
                 menuPauseConsole();
                 break;
 
             case 8: // DELETION OF NODE AT THE END
                 menuClearConsole();
                 deleteAtStartOrEnd(0);
                 menuPauseConsole();
                 break;
 
             case 9: // DELETION OF NODE BY VALUE
                 menuClearConsole();
                 deleteByValue();
                 menuPauseConsole();
                 break;
 
             case 10: // EMPTY LINKED LIST
                 menuClearConsole();
                 emptyList();
                 menuPauseConsole();
                 break;
 
             case 11: // EXIT THE PROGRAM
                 return 0;
         }
     }
 }
 
 // FUNCATIONS DEFINITION: ///////////////////////////////////////////////////////////////////////////////////////
 
 // MENU FUNCTIONS: //
 
 /**
  * @brief Gets a validated integer choice from the user within a specified range.
  *
  * This function reads input, validates it as an integer, and ensures
  * it falls within the specified range. If the input is invalid, it returns -1.
  *
  * @param min Minimum valid value (0 or negative means no lower limit).
  * @param max Maximum valid value (0 or negative means no upper limit).
  * @return The validated integer choice, or -1 if invalid.
  */
 int menuChoice(int min, int max) {
     char buffer[100]; // Temporary buffer for user input
     int choice;
 
     printf("\nChoice: ");
     readInput(buffer, sizeof(buffer));
 
     // Validate input as an integer
     if (!isValidNumber(buffer, 0)) {
         printf("ERROR: Invalid input. Please enter a valid number.\n");
         menuPauseConsole();
         return -1; // Indicate invalid input
     }
 
     choice = atoi(buffer);
 
     // Check if within the allowed range
     if ((min > 0 && choice < min) || (max > 0 && choice > max)) {
         printf("ERROR: Please enter a number between %d and %d.\n\n", min, max);
         menuPauseConsole();
         return -1; // Indicate invalid input
     }
 
     return choice; // Valid input, return choice
 }
 
 /**
  * @brief Clears the console screen (cross-platform support).
  */
 void menuPauseConsole() {
     printf("\nPress Enter to continue...");
     getchar();
 }
 
 /**
  * @brief Waits for user input before continuing execution.
  */
 void menuClearConsole(){
 	
     #ifdef _WIN32
         system("cls");
     #else
         system("clear");
     #endif
 }
 
 /**
  * @brief Displays the list name and its field details.
  *
  * If no list has been created, it prompts the user to create one.
  * Otherwise, it prints the list name along with its fields and corresponding data types.
  */
 void menuDisplayList() {
 	int i;
     if (currentList == NULL) {
         printf(
             "Welcome to \"Double Linked List Generator\"\n"
             "This program allows users to dynamically create custom lists with custom nodes and fields!\n\n"
             "INFO: No list has been created yet.\n"
             "INFO: Please select \"[1] CREATION OF LIST AND NODE\" to create your very own custom list.\n");
         return;
     }
 
     printf("\nList Name: %s\n", currentList->name);
     
     for (i = 0; i < currentList->fieldCount; i++) {
         // Convert field type to string
         const char *type;
         switch (currentList->fieldTypes[i]) {
             case 1: type = "Integer"; break;
             case 2: type = "Float"; break;
             case 3: type = "Character"; break;
             case 4: type = "String"; break;
             default: type = "Unknown"; break;
         }
 
         // Display field details
         printf(" - <%s> %s\n", type, currentList->fieldNames[i]);
     }
 }
 
 // GENERAL FUNCTIONS: //
 
 /**
  * @brief Validates if a given string represents a valid integer or float.
  *
  * This function checks whether a string is a valid integer or floating-point number.
  * It supports optional negative signs and ensures that the number contains at least one digit.
  *
  * @param input The string to validate.
  * @param allowFloat If 1, allows floating-point numbers; if 0, only integers are allowed.
  * @return 1 if the string is a valid number, 0 otherwise.
  */
 int isValidNumber(char *input, int allowFloat) {
     if (input == NULL || input[0] == '\0') return 0; // Empty string is invalid
 
     int i = 0, dotCount = 0, digitCount = 0;
 
     // Allow optional negative sign
     if (input[i] == '-') {  
         i++;
         if (input[i] == '\0') return 0; // "-" alone is invalid
     }
 
     // Iterate through characters
     for (; input[i] != '\0'; i++) {
         if (input[i] == '.') {
             // If float is not allowed or more than one dot appears, return invalid
             if (!allowFloat || ++dotCount > 1) return 0;
         } else if (isdigit(input[i])) {
             digitCount++;
         } else {
             return 0; // Invalid character found
         }
     }
 
     // Ensure the input contains at least one digit
     return digitCount > 0;
 }
 
 /**
  * @brief Reads a line of input from the user and removes the trailing newline character.
  *
  * This function safely reads user input into a buffer, ensuring that the string does not exceed
  * the specified size. It also removes the newline character (`\n`) at the end if present.
  *
  * @param buffer Pointer to the character array where the input will be stored.
  * @param size Maximum number of characters to read (including the null terminator).
  */
 void readInput(char *buffer, int size) {
 	int i;
     if (fgets(buffer, size, stdin) == NULL) {
         buffer[0] = '\0'; // If input fails, ensure buffer is empty
         return;
     }
 
     buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character if present
 }
 
 /**
  * @brief Creates a new node and allocates memory for its fields.
  *
  * This function dynamically allocates memory for a new node structure,
  * as well as its field values. If memory allocation fails, the function
  * frees any allocated memory and returns NULL.
  *
  * @param list Pointer to the list structure to determine field count.
  * @return Pointer to the newly created node, or NULL if memory allocation fails.
  */
 node* createNode(list *list) {
     // Allocate memory for the node structure
     node *newNode = (node*)malloc(sizeof(node));
     if (!newNode) {
         printf("ERROR: Memory allocation failed for node.\n");
         return NULL;
     }
 
     // Allocate memory for the field array (array of character pointers)
     newNode->field = (char**)malloc(sizeof(char*) * list->fieldCount);
     int i, j;
	 if (!newNode->field) {
         printf("ERROR: Memory allocation failed for fields.\n");
         free(newNode);
         return NULL;
     }
 
     // Allocate memory for each field string (array of characters)
     for (i = 0; i < list->fieldCount; i++) {
         newNode->field[i] = (char*)malloc(sizeof(char) * 100);
         if (!newNode->field[i]) {
             printf("ERROR: Memory allocation failed for field[%d].\n", i);
 
             // Free all previously allocated fields
             for (j = 0; j < i; j++) {
                 free(newNode->field[j]);
             }
             free(newNode->field); // Free the field array
             free(newNode); // Free the node structure
             return NULL;
         }
     }
 
     // Initialize pointers to avoid undefined behavior
     newNode->next = NULL;
     newNode->prev = NULL;
 
     return newNode;
 }
 
 /**
  * @brief Checks if a list exists and optionally if it contains nodes.
  *
  * This function verifies whether a linked list has been created (`currentList` is not NULL).
  * If `checkNodes` is enabled, it also checks if the list contains at least one node.
  * The function can either print error messages or run silently based on `suppressWarnings`.
  *
  * @param checkNodes If 1, also checks if the list contains nodes.
  * @param suppressWarnings If 1, suppresses error messages.
  * @return 1 if the list is available (and contains nodes if `checkNodes` is enabled), otherwise 0.
  */
 int isListAvailable(int checkNodes, int suppressWarnings) {
     if (currentList == NULL) {
         if (!suppressWarnings) {
             printf("ERROR: No list has been created yet.\n"
                    "INFO: Please select \"[1] CREATION OF LIST AND NODE\" to create your custom list.\n");
         }
         return 0;
     }
 
     if (checkNodes && currentList->start == NULL) {
         if (!suppressWarnings) {
             printf("ERROR: No nodes available in the list.\n"
                    "INFO: Please create at least one node.\n");
         }
         return 0;
     }
 
     return 1;
 }
 
 /**
  * @brief Creates a new node and fills it with user-provided data.
  *
  * This function prompts the user for input for each field in the linked list.
  * It validates user input based on the field type, ensuring correctness.
  * 
  * @return Pointer to the newly created and filled node.
  */
 node* createAndFillNode() {
 	int i;
     if (!isListAvailable(0,0)) return NULL; // Ensure a list exists before proceeding.
 
     node* newNode = createNode(currentList);
 
     for (i = 0; i < currentList->fieldCount; i++) {
         while (1) {
             printf("Enter %s: ", currentList->fieldNames[i]);
             readInput(newNode->field[i], 100);
 
             // Ensure the input is not empty before proceeding
             if (newNode->field[i][0] == '\0') {
                 printf("ERROR: Input cannot be empty. Please try again.\n");
                 continue;
             }
 
             // Validate input based on field type
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
 
             break; // Exit loop if input is valid
         }
     }
 
     return newNode;
 }
 
 /**
  * @brief Frees the memory allocated for a node and its fields.
  *
  * This function safely frees all dynamically allocated memory associated with a node,
  * including its field values and the field pointer array. It ensures that memory is
  * only freed if it was allocated, preventing potential segmentation faults.
  *
  * @param target Pointer to the node to be freed.
  */
 void freeNode(node* target) {
 	int i;
     if (target == NULL) return; // If the node is already NULL, no need to free.
     if (currentList == NULL) return; // Ensure currentList exists before accessing fieldCount.
 
     // Free each allocated field (if target->field exists)
     if (target->field != NULL) {
         for (i = 0; i < currentList->fieldCount; i++) {
             free(target->field[i]); // Safe to free even if NULL
         }
         free(target->field); // Free the array of field pointers
     }
 
     free(target); // Free the node itself
 }
 
 
 /**
  * @brief Creates a new linked list with user-defined fields.
  *
  * This function initializes a new list, allowing the user to specify field names and types.
  * Memory is dynamically allocated for list metadata, and the function prevents duplicate list creation.
  * If an error occurs (e.g., memory allocation failure), all allocated resources are freed safely.
  */
 void createList() {
 	int i;
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
     currentList->end = NULL;
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
 
         fieldChoice = menuChoice(1,5);
         
         if (fieldChoice == 5) {
             if (currentList->fieldCount == 0) {
                 printf("\nERROR: You must add at least one field before finishing.\n");
                 continue;
             }
             break;
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
             for (i = 0; i < currentList->fieldCount - 1; i++) {
                 free(currentList->fieldNames[i]);
             }
 
             free(currentList->fieldNames);
             free(currentList->fieldTypes);
             free(currentList);
             currentList = NULL;
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
     
     menuClearConsole();
     printf("INFO: List '%s' created successfully with %d fields.\n", currentList->name, currentList->fieldCount);
     menuDisplayList();
 }
 
 /**
  * @brief Displays all nodes in the linked list with aligned formatting.
  *
  * This function prints each node's field values in a structured format, ensuring
  * that all columns align properly, regardless of field name length.
  */
 void displayNode() {
 	int i;
     if (!isListAvailable(1, 1)) {
         menuClearConsole();
         printf(
             "ERROR: No list or nodes available.\n"
             "INFO: Please select \"[1] CREATION OF LIST AND NODE\" to create a custom list.\n"
             "INFO: If a list has been created, please add at least one node.\n");
         menuPauseConsole();
         return;
     }
 
     menuClearConsole();
     printf("\n%s:\n", currentList->name);
 
     // Determine the longest field name for column alignment
     int maxFieldWidth = 0;
     for (i = 0; i < currentList->fieldCount; i++) {
         int fieldNameLength = strlen(currentList->fieldNames[i]);
         if (fieldNameLength > maxFieldWidth) {
             maxFieldWidth = fieldNameLength;
         }
     }
 
     node *temp = currentList->start;
     
     // Display all nodes with proper alignment
     while (temp) {
         for (i = 0; i < currentList->fieldCount; i++) {
             printf("%-*s : %-15s | ", maxFieldWidth, currentList->fieldNames[i], temp->field[i]);
         }
         printf("\n");
         temp = temp->next;
     }
 
     menuPauseConsole();
 }
 
 
 /**
  * @brief Searches for nodes based on a user-selected field and value.
  *
  * This function allows the user to select a field and enter a value to search for.
  * It then scans the list and returns all matching nodes.
  *
  * @param matchedNodes Pointer to an array of pointers to store matched nodes.
  * @param matchCount Pointer to store the number of matched nodes.
  * @return The number of matched nodes found.
  */
 int searchNode(node*** matchedNodes, int* matchCount) {
 	int i, j;
     if (!isListAvailable(1,0) || currentList->fieldCount == 0) return 0;
 
     menuClearConsole();
     printf("Select the field to search on:\n");
     for (i = 0; i < currentList->fieldCount; i++) {
         printf("[%d] %s\n", i + 1, currentList->fieldNames[i]);
     }
 
     int fieldChoice = menuChoice(1, currentList->fieldCount);
     int fieldIndex = fieldChoice - 1;
 
     char searchValue[100];
     printf("Enter the value to search for in %s: ", currentList->fieldNames[fieldIndex]);
     readInput(searchValue, sizeof(searchValue));
 
     *matchCount = 0;
     node* temp = currentList->start;
 
     // Count matches first
     while (temp) {
         if (strcmp(temp->field[fieldIndex], searchValue) == 0) {
             (*matchCount)++;
         }
         temp = temp->next;
     }
 
     if (*matchCount == 0) {
         printf("INFO: No matching nodes found for %s = %s\n", currentList->fieldNames[fieldIndex], searchValue);
         *matchedNodes = NULL;
         return 0;
     }
 
     // Allocate memory only for matched nodes
     *matchedNodes = malloc(sizeof(node*) * (*matchCount));
     if (*matchedNodes == NULL) {
         printf("ERROR: Memory allocation failed.\n");
         *matchCount = 0;
         menuPauseConsole();
         return 0;
     }
 
     // Store matching nodes
     temp = currentList->start;
     int index = 0;
     while (temp) {
         if (strcmp(temp->field[fieldIndex], searchValue) == 0) {
             (*matchedNodes)[index++] = temp;
         }
         temp = temp->next;
     }
 
     // Display results
     menuClearConsole();
     printf("INFO: Matched! %d result%s found:\n", *matchCount, (*matchCount > 1) ? "s" : "");
 
     // Determine maximum field name length for formatting
     int maxFieldWidth = 0;
     for (j = 0; j < currentList->fieldCount; j++) {
         int fieldNameLength = strlen(currentList->fieldNames[j]);
         if (fieldNameLength > maxFieldWidth) {
             maxFieldWidth = fieldNameLength;
         }
     }
 
     // Print results with aligned columns
     for (i = 0; i < *matchCount; i++) {
         printf("[%d] ", i + 1);
         for (j = 0; j < currentList->fieldCount; j++) {
             printf("%-*s: %-15s | ", maxFieldWidth, currentList->fieldNames[j], (*matchedNodes)[i]->field[j]);
         }
         printf("\n");
     }
 
     
     return *matchCount;
 }
 
 /**
  * @brief Selects a node by searching based on a field value.
  *
  * This function calls `searchNode()` to find matching nodes. If only one match is found,
  * it is automatically selected. If multiple matches are found, the user is prompted
  * to select one. The selected node is returned for further operations.
  *
  * @return Pointer to the selected node, or NULL if no valid selection is made.
  */
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
         printf("\nAutomatically selecting the only match.\n");
     } else {
         printf("Select a match (1-%d): ", matchCount);
         
         // Ensure the user selects a valid index
         int selectedIndex = menuChoice(1, matchCount) - 1;
     
         selectedNode = matchedNodes[selectedIndex];
     }    
 
     // Free allocated array (but not the selected node)
     free(matchedNodes);
     return selectedNode;
 }
 
 // DOUBLE LINKED LIST OPERATION FUNCTIONS: //
 
 /**
  * @brief Inserts a new node at the start or end of the linked list.
  *
  * This function creates a new node and inserts it at the start if `insertAtStart` is 1,
  * or at the end if `insertAtStart` is 0. It correctly updates the `start` and `end` pointers.
  *
  * @param insertAtStart If 1, inserts at the start; if 0, inserts at the end.
  */
 void insertAtStartOrEnd(int insertAtStart) {
     if (!isListAvailable(0,0)) return;
 
     node* newNode = createAndFillNode();
 
     if (currentList->start == NULL) {
         // List is empty, new node becomes both start and end
         currentList->start = newNode;
         currentList->end = newNode;
         newNode->next = NULL;
         newNode->prev = NULL;
     } else if (insertAtStart) {
         // Insert at the START
         newNode->prev = NULL;
         newNode->next = currentList->start;
         currentList->start->prev = newNode;
         currentList->start = newNode;
     } else {
         // Insert at the END
         newNode->next = NULL;
         newNode->prev = currentList->end;
         currentList->end->next = newNode;
         currentList->end = newNode;
     }
 
     printf("INFO: Node successfully inserted at the %s.\n", insertAtStart ? "start" : "end");
 }
 
 /**
  * @brief Inserts a new node before or after a selected node in the list.
  *
  * This function allows inserting a new node before or after a chosen node.
  * If inserting before the first node, `currentList->start` is updated.
  * If inserting after the last node, `currentList->end` is updated.
  *
  * @param insertBefore If 1, inserts before the target node; if 0, inserts after.
  */
 void insertBeforeOrAfter(int insertBefore) {
     if (!isListAvailable(0,0)) return;
 
     printf("Insert node %s the selected node.\n", insertBefore ? "before" : "after");
     node* target = selectNodeByField();
     if (target == NULL) return;
 
     node* newNode = createAndFillNode();
 
     if (insertBefore) {
         // Insert BEFORE target
         newNode->next = target;
         newNode->prev = target->prev;
 
         if (target->prev != NULL) {
             target->prev->next = newNode;
         } else {
             currentList->start = newNode;  // If inserting before first node, update head
         }
 
         target->prev = newNode;
     } else {
         // Insert AFTER target
         newNode->next = target->next;
         newNode->prev = target;
 
         if (target->next != NULL) {
             target->next->prev = newNode;
         } else {
             currentList->end = newNode;  // If inserting after last node, update tail
         }
 
         target->next = newNode;
     }
 
     printf("Node successfully inserted %s the selected node.\n", insertBefore ? "before" : "after");
 }
 
 /**
  * @brief Deletes a node from either the start or end of the linked list.
  *
  * This function removes the first node or the last node.
  * It correctly updates the `start` and `end` pointers and frees the node's memory.
  *
  * @param deleteAtStart If 1, deletes from the start; if 0, deletes from the end.
  */
 void deleteAtStartOrEnd(int deleteAtStart) {
     if (!isListAvailable(0,0)) return;
 
     // Determine which node to delete
     node* delNode = deleteAtStart ? currentList->start : currentList->end;
 
     if (delNode == NULL) {
         printf("List is already empty.\n");
         return;
     }
 
     if (deleteAtStart) {
         // Delete from START
         currentList->start = delNode->next;
         if (currentList->start != NULL) {
             currentList->start->prev = NULL;
         } else {
             currentList->end = NULL;  // List is now empty
         }
     } else {
         // Delete from END
         currentList->end = delNode->prev;
         if (currentList->end != NULL) {
             currentList->end->next = NULL;
         } else {
             currentList->start = NULL;  // List is now empty
         }
     }
 
     // Free the deleted node
     freeNode(delNode);
 
     printf("Node successfully deleted from the %s.\n", deleteAtStart ? "start" : "end");
 }
 
 /**
  * @brief Deletes a node by its value.
  *
  * This function searches for a node based on user input, removes it from the doubly linked list,
  * updates pointers accordingly, and frees allocated memory.
  *
  * If the node is the head, `currentList->start` is updated.
  * If the node is the tail, `currentList->end` is updated.
  */
 void deleteByValue() {
 	int i;
     if (!isListAvailable(0,0)) return;
 
     printf("Select the node to delete.\n");
     node* target = selectNodeByField();
     if (target == NULL) return;
 
     // If the node to delete is the head
     if (target == currentList->start) {
         currentList->start = target->next;
         if (currentList->start) currentList->start->prev = NULL;
     } 
     // If the node to delete is the tail
     else if (target == currentList->end) {
         currentList->end = target->prev;
         if (currentList->end) currentList->end->next = NULL;
     } 
     // If the node is in the middle
     else {
         target->prev->next = target->next;
         target->next->prev = target->prev;
     }
 
     // Free memory allocated for the node
     freeNode(target);
 
     printf("INFO: Selected node deleted successfully.\n");
 }
 
 /**
  * @brief Empties the entire linked list, deleting all nodes and metadata.
  *
  * This function:
  * 1. Frees all nodes in the list.
  * 2. Frees metadata fields (`fieldNames`, `fieldTypes`).
  * 3. Frees the list itself and sets `currentList = NULL`.
  */
 void emptyList() {
     if (!isListAvailable(0,0)) return;
 
     // Step 1: Free all nodes
     node *temp = currentList->start;
     while (temp != NULL) {
         node *nextNode = temp->next;
         freeNode(temp);
         temp = nextNode;
     }
 
     // Step 2: Free field names
     int i;
     
     for (i = 0; i < currentList->fieldCount; i++) {
         free(currentList->fieldNames[i]);
     }
     free(currentList->fieldNames);
 
     // Step 3: Free field types
     free(currentList->fieldTypes);
 
     // Step 4: Free the list itself
     free(currentList);
     currentList = NULL;
 
     printf("INFO: The entire list has been deleted, including metadata.\n");
 } 
