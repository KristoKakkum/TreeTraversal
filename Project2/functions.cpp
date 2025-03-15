#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"

#pragma warning(disable : 4996)

/* ------------------------------------------------------------------
   HELPER FUNCTIONS
   ------------------------------------------------------------------ */

   /**
 * This function checks if the provided identifier (pID) has the correct format:
 * - It should consist of exactly two words separated by a single space.
 * - The first word starts with an uppercase letter [A-Z] followed by lowercase letters [a-z].
 * - The second word also starts with an uppercase letter followed by lowercase letters.
 *
 * Returns 1 if the format is valid, otherwise returns 0.
 */
static int IsValidIDFormat(const char* pID)
{
    if (!pID) return 0; // Null check

    const char* spacePos = strchr(pID, ' '); // Find the first space in the string
    if (!spacePos) {
        // If no space exists, the identifier doesn't have two words
        return 0;
    }

    int len = (int)strlen(pID);
    int idxSpace = (int)(spacePos - pID); // Position of the space in the string
    if (idxSpace == 0 || idxSpace == len - 1) {
        // If the space is at the start or end, the format is invalid
        return 0;
    }

    // Check for a second space
    if (strchr(spacePos + 1, ' ')) {
        return 0; // If another space is found, it's invalid
    }

    // Validate the first word (Word1): Uppercase first letter followed by lowercase letters
    if (pID[0] < 'A' || pID[0] > 'Z') return 0;
    for (int i = 1; i < idxSpace; i++) {
        if (pID[i] < 'a' || pID[i] > 'z') return 0;
    }

    // Validate the second word (Word2): Same rules as Word1
    int start2 = idxSpace + 1;
    if (pID[start2] < 'A' || pID[start2] > 'Z') return 0;
    for (int i = start2 + 1; i < len; i++) {
        if (pID[i] < 'a' || pID[i] > 'z') return 0;
    }

    return 1; // Valid identifier
}

/**
 * This function checks if the given identifier (pID) already exists in the structure.
 *
 * Parameters:
 * - pHead: Pointer to the head of the HeaderC linked list.
 * - pID: The identifier to search for.
 *
 * Returns 1 if the identifier exists, otherwise returns 0.
 */
static int IsDuplicateID(HeaderC* pHead, const char* pID)
{
    while (pHead) { // Traverse each HeaderC node
        for (int i = 0; i < 26; i++) { // Check all linked lists for each letter
            Object2* pObj = (Object2*)pHead->ppObjects[i]; // Get the linked list for the current letter
            while (pObj) { // Traverse the linked list
                if (strcmp(pObj->pID, pID) == 0) {
                    return 1; // Found the duplicate identifier
                }
                pObj = pObj->pNext; // Move to the next object in the list
            }
        }
        pHead = pHead->pNext; // Move to the next HeaderC node
    }
    return 0; // Identifier not found
}


/* ------------------------------------------------------------------
   1) PrintObjects
   ------------------------------------------------------------------ */
   /**
    * This function prints all objects in the HeaderC linked list.
    *
    * Parameters:
    * - pStruct4: Pointer to the head of the HeaderC structure.
    *
    * The function iterates through the HeaderC list and prints each object's details,
    * including its identifier (pID), code, and creation time.
    */
void PrintObjects(HeaderC* pStruct4)
{
    int count = 1; // Counter for numbering the objects
    while (pStruct4) { // Traverse the HeaderC list
        printf("HeaderC cBegin: %c\n", pStruct4->cBegin); // Print the starting letter of the HeaderC node
        for (int i = 0; i < 26; i++) { // Check each linked list for the letter range ('a' to 'z')
            Object2* pObj = (Object2*)pStruct4->ppObjects[i]; // Get the linked list for the current letter
            while (pObj) { // Traverse the linked list
                printf("%d) %s %lu %02d:%02d:%02d\n", // Print object details
                    count,
                    pObj->pID,
                    pObj->Code,
                    pObj->pTime1->Hour,
                    pObj->pTime1->Minute,
                    pObj->pTime1->Second);
                count++; // Increment the counter
                pObj = pObj->pNext; // Move to the next object
            }
        }
        pStruct4 = pStruct4->pNext; // Move to the next HeaderC node
    }
}


/* ------------------------------------------------------------------
   2) InsertNewObject
   ------------------------------------------------------------------ */
   /**
    * Inserts a new object into the HeaderC structure.
    *
    * @param ppStruct4: Pointer to the pointer of the first HeaderC node.
    * @param pNewID: Pointer to the new identifier string.
    * @param NewCode: Code for the new object.
    * @return: 1 if the insertion is successful, 0 otherwise.
    */
int InsertNewObject(HeaderC** ppStruct4, char* pNewID, int NewCode)
{
    if (!ppStruct4 || !(*ppStruct4) || !pNewID || strlen(pNewID) < 1) {
        printf("Insert error: invalid parameters.\n");
        return 0; // Invalid inputs.
    }

    if (!IsValidIDFormat(pNewID)) {
        printf("Insert error: invalid ID format '%s'\n", pNewID);
        return 0; // Invalid identifier format.
    }

    if (IsDuplicateID(*ppStruct4, pNewID)) {
        printf("Insert error: duplicate ID '%s'\n", pNewID);
        return 0; // Identifier already exists.
    }

    char cBegin = pNewID[0]; // First letter of the identifier.
    HeaderC* current = *ppStruct4; // Start from the head of the HeaderC list.
    HeaderC* prev = NULL;

    while (current && current->cBegin < cBegin) { // Find or create the right HeaderC node.
        prev = current;
        current = current->pNext;
    }

    if (!current || current->cBegin != cBegin) { // Create a new HeaderC node.
        HeaderC* newHeader = (HeaderC*)malloc(sizeof(HeaderC));
        if (!newHeader) {
            printf("Insert error: out of memory.\n");
            return 0;
        }
        newHeader->cBegin = cBegin;
        newHeader->ppObjects = (void**)calloc(26, sizeof(void*));
        newHeader->pNext = current;
        if (prev) prev->pNext = newHeader; // Insert the new node in the list.
        else *ppStruct4 = newHeader;
        current = newHeader;
    }

    int index = 0; // Determine the index for the linked list.
    if (strlen(pNewID) > 1) {
        index = pNewID[1] - 'a';
        if (index < 0 || index >= 26) index = 0;
    }

    Object2* newObj = (Object2*)malloc(sizeof(Object2)); // Allocate memory for the new object.
    if (!newObj) {
        printf("Insert error: out of memory (Object2).\n");
        return 0;
    }
    newObj->pID = strdup(pNewID); // Copy the identifier.
    newObj->Code = (unsigned long)NewCode;

    // Assign a timestamp to the new object.
    newObj->pTime1 = (Time1*)malloc(sizeof(Time1));
    time_t rawTime;
    time(&rawTime);
    struct tm* tinfo = localtime(&rawTime);
    newObj->pTime1->Hour = tinfo->tm_hour;
    newObj->pTime1->Minute = tinfo->tm_min;
    newObj->pTime1->Second = tinfo->tm_sec;

    // Insert the object into the linked list.
    newObj->pNext = (Object2*)current->ppObjects[index];
    current->ppObjects[index] = newObj;

    return 1; // Successful insertion.
}


/* ------------------------------------------------------------------
   3) RemoveExistingObject
   ------------------------------------------------------------------ */
   /**
    * Removes an object with the specified identifier from the HeaderC structure.
    *
    * @param ppStruct4: Pointer to the pointer of the first HeaderC node.
    * @param pExistingID: Pointer to the identifier of the object to remove.
    * @return: Pointer to the removed object, or NULL if not found.
    */
Object2* RemoveExistingObject(HeaderC** ppStruct4, char* pExistingID)
{
    if (!ppStruct4 || !(*ppStruct4) || !pExistingID || strlen(pExistingID) < 1) {
        printf("Remove error: invalid parameters.\n");
        return NULL;
    }

    char cBegin = pExistingID[0]; // First letter of the identifier.
    HeaderC* current = *ppStruct4; // Start from the head.
    HeaderC* prevHeader = NULL;

    while (current && current->cBegin != cBegin) { // Find the right HeaderC node.
        prevHeader = current;
        current = current->pNext;
    }

    if (!current) {
        printf("Remove error: '%s' not found.\n", pExistingID);
        return NULL;
    }

    int index = 0; // Determine the list index.
    if (strlen(pExistingID) > 1) {
        index = pExistingID[1] - 'a';
        if (index < 0 || index >= 26) index = 0;
    }

    Object2* prevObj = NULL;
    Object2* currObj = (Object2*)current->ppObjects[index]; // Start from the linked list head.

    while (currObj && strcmp(currObj->pID, pExistingID) != 0) { // Search for the object.
        prevObj = currObj;
        currObj = currObj->pNext;
    }

    if (!currObj) {
        printf("Remove error: '%s' not found.\n", pExistingID);
        return NULL;
    }

    if (prevObj) prevObj->pNext = currObj->pNext; // Unlink the object.
    else current->ppObjects[index] = currObj->pNext;

    // Check if the HeaderC node is now empty.
    int isEmpty = 1;
    for (int i = 0; i < 26; i++) {
        if (current->ppObjects[i]) {
            isEmpty = 0;
            break;
        }
    }

    if (isEmpty) { // Remove the empty HeaderC node.
        if (!prevHeader) *ppStruct4 = current->pNext;
        else prevHeader->pNext = current->pNext;
        free(current->ppObjects);
        free(current);
    }

    return currObj; // Return the removed object.
}


/* ------------------------------------------------------------------
   4) CreateBinaryTree
   ------------------------------------------------------------------ */
   /**
    * Converts the objects in the HeaderC structure into a binary search tree (BST).
    *
    * @param pStruct4: Pointer to the head of the HeaderC structure.
    * @return: Pointer to the root of the BST.
    */
    /**
     * CreateBinaryTree:
     *    Builds a binary search tree (BST) from all `Object2` items in the
     *    `HeaderC` structure. The BST is keyed by `Object2->Code`.
     *
     *    This function prints the order in which nodes are inserted into
     *    the BST along with their relationships (parent-child).
     *
     * Parameters:
     *    @param pStruct4: Pointer to the `HeaderC` structure containing
     *                     the list of `Object2` objects.
     *
     * Returns:
     *    @return Node*: Pointer to the root of the created BST.
     */
Node* CreateBinaryTree(HeaderC* pStruct4) {
    Node* root = NULL;        // Initialize the root of the BST to NULL
    int insertOrder = 1;      // Keep track of the insertion order

    // Traverse through all HeaderC nodes
    while (pStruct4) {
        // Loop through the array of 26 object lists in the current HeaderC node
        for (int i = 0; i < 26; i++) {
            Object2* pObj = (Object2*)pStruct4->ppObjects[i];  // Get the object list
            while (pObj) {  // Traverse each linked list of Object2 objects
                // Allocate memory for a new BST node
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->pObject = pObj;   // Store the object pointer in the node
                newNode->pLeft = NULL;     // Initialize the left child as NULL
                newNode->pRight = NULL;    // Initialize the right child as NULL

                // If the BST is empty, this node becomes the root
                if (!root) {
                    root = newNode;  // Assign the root
                    printf("[%d] Root created: ID=%s Code=%lu\n",
                        insertOrder, ((Object2*)newNode->pObject)->pID,
                        ((Object2*)newNode->pObject)->Code);
                }
                else {
                    // Otherwise, insert the node into the correct position
                    Node* curr = root;   // Start from the root
                    Node* parent = NULL; // Track the parent node
                    unsigned long newCode = ((Object2*)newNode->pObject)->Code;

                    // Traverse the BST to find the correct position
                    while (curr) {
                        parent = curr;  // Keep track of the parent
                        unsigned long currCode = ((Object2*)curr->pObject)->Code;
                        if (newCode < currCode) {
                            curr = curr->pLeft;  // Move to the left child
                        }
                        else {
                            curr = curr->pRight;  // Move to the right child
                        }
                    }

                    // Attach the new node to the correct parent
                    if (newCode < ((Object2*)parent->pObject)->Code) {
                        parent->pLeft = newNode;  // Insert as the left child
                        printf("[%d] Inserted LEFT of %s: ID=%s Code=%lu\n",
                            insertOrder, ((Object2*)parent->pObject)->pID,
                            ((Object2*)newNode->pObject)->pID, newCode);
                    }
                    else {
                        parent->pRight = newNode;  // Insert as the right child
                        printf("[%d] Inserted RIGHT of %s: ID=%s Code=%lu\n",
                            insertOrder, ((Object2*)parent->pObject)->pID,
                            ((Object2*)newNode->pObject)->pID, newCode);
                    }
                }

                insertOrder++;  // Increment the insertion order
                pObj = pObj->pNext;  // Move to the next object in the linked list
            }
        }

        // Move to the next HeaderC node
        pStruct4 = pStruct4->pNext;
    }

    return root;  // Return the root of the BST
}

/**
 * TreeTraversal:
 *    Performs an in-order traversal of the BST (left -> node -> right).
 *    Displays each node's ID, Code, and its relationship to the parent node.
 *    Also highlights the root node for better visibility.
 *
 * Parameters:
 *    @param pTree: Pointer to the root of the BST.
 * Returns:
 *    @return: None.
 */
void TreeTraversal(Node* pTree)
{
    if (!pTree) {
        printf("BST is empty.\n");
        return;
    }

    Stack* pStack = NULL; // Stack for non-recursive traversal
    Node* current = pTree; // Current node pointer
    Node* root = pTree;    // Pointer to the root node

    // A simple array-based map to track parent-child relationships
    Node* parentMap[1000] = { NULL }; // Adjust size based on expected number of nodes
    int mapIndex = 0;

    while (1) {
        // Push all left nodes onto the stack
        while (current) {
            Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
            newStackNode->pObject = current; // Store the current node in the stack
            newStackNode->pNext = pStack;
            pStack = newStackNode;

            // Track the parent of the left child
            if (current->pLeft) {
                parentMap[mapIndex++] = current;
            }

            current = current->pLeft; // Move to the left child
        }

        // If stack is empty, traversal is complete
        if (!pStack) {
            break;
        }

        // Pop the top node from the stack
        Stack* top = pStack;
        current = (Node*)top->pObject;
        pStack = pStack->pNext;
        free(top); // Free the stack node

        // Print the current node
        Object2* pObj = (Object2*)current->pObject;

        if (current == root) {
            printf("ROOT -> ID: %-30s Code: %lu\n", pObj->pID, pObj->Code);
        }
        else {
            // Find the parent node
            Node* parent = NULL;
            for (int i = 0; i < mapIndex; i++) {
                if (parentMap[i]->pLeft == current || parentMap[i]->pRight == current) {
                    parent = parentMap[i];
                    break;
                }
            }

            Object2* parentObj = (Object2*)parent->pObject;
            printf("%s -> ID: %-30s Code: %lu (Parent: %s)\n",
                (current == parent->pLeft ? "LEFT" : "RIGHT"),
                pObj->pID,
                pObj->Code,
                parentObj->pID);
        }

        // Track the parent of the right child
        if (current->pRight) {
            parentMap[mapIndex++] = current;
        }

        // Move to the right child
        current = current->pRight;
    }
}


/**
 * DeleteTreeNode:
 *    Deletes a node with a specific `Code` from the BST.
 *    Maintains the BST structure after deletion.
 *
 * Parameters:
 *    @param pTree: Pointer to the root of the BST.
 *    @param Code: The code of the node to be deleted.
 *
 * Returns:
 *    @return Node*: Pointer to the new root of the BST.
 */
Node* DeleteTreeNode(Node* pTree, unsigned long int Code)
{
    if (!pTree) return NULL; // BST is empty

    Node* parent = NULL;
    Node* current = pTree;

    // Step 1: Search for the node to delete
    while (current && ((Object2*)current->pObject)->Code != Code) {
        parent = current;
        if (Code < ((Object2*)current->pObject)->Code) {
            current = current->pLeft;
        }
        else {
            current = current->pRight;
        }
    }

    if (!current) {
        printf("BST delete: Code %lu not found.\n", Code);
        return pTree; // Node with the specified code not found
    }

    // Step 2: Handle the three deletion cases

    // Case 1: Node has no children (leaf node)
    if (!current->pLeft && !current->pRight) {
        if (!parent) { // Deleting the root node
            free(current);
            return NULL;
        }

        if (parent->pLeft == current) {
            parent->pLeft = NULL;
        }
        else {
            parent->pRight = NULL;
        }
        free(current);
    }

    // Case 2: Node has one child
    else if (!current->pLeft || !current->pRight) {
        Node* child = (current->pLeft) ? current->pLeft : current->pRight;

        if (!parent) { // Deleting the root node with one child
            free(current);
            return child;
        }

        if (parent->pLeft == current) {
            parent->pLeft = child;
        }
        else {
            parent->pRight = child;
        }
        free(current);
    }

    // Case 3: Node has two children
    else {
        // Find the in-order successor (leftmost node in the right subtree)
        Node* succParent = current;
        Node* successor = current->pRight;
        while (successor->pLeft) {
            succParent = successor;
            successor = successor->pLeft;
        }

        // Replace the current node's data with successor's data
        ((Object2*)current->pObject)->Code = ((Object2*)successor->pObject)->Code;
        ((Object2*)current->pObject)->pID = strdup(((Object2*)successor->pObject)->pID);

        // Remove the successor node
        if (succParent->pLeft == successor) {
            succParent->pLeft = successor->pRight;
        }
        else {
            succParent->pRight = successor->pRight;
        }
        free(successor);
    }

    return pTree; // Return the updated root of the BST
}


