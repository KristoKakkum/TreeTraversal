#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"


/* ------------------------------------------------------------------
   main()
   ------------------------------------------------------------------ */
/*int main()
{
    // 1) N=35 => create the base structure
    HeaderC* pStruct4 = GetStruct4(2, 35);
    if (!pStruct4) {
        printf("Failed to create structure.\n");
        return 1;
    }

    // 2) Print the base structure
    printf("=== INITIAL STRUCTURE (N=35) ===\n");
    PrintObjects(pStruct4);

    // 3) Insert in specified order
    const char* insertIDs[] = {
        "Dx Gz", "Dx Ga", "Db Aa", "Dk Za", "Dr Wa",
        "Aa Aa", "Ab Ba", "Za Aa", "Za Ab", "Za Ba",
        "Wx Xa", "Wx Aa", "zb Kk", "Zc ca", "Dr Wa",
        "ZB kk", "Fa", "Fa_Fa"
    };
    int nInserts = (int)(sizeof(insertIDs) / sizeof(insertIDs[0]));

    printf("\n=== INSERTING OBJECTS ===\n");
    int codeVal = 100;
    for (int i = 0; i < nInserts; i++) {
        int rc = InsertNewObject(&pStruct4, (char*)insertIDs[i], codeVal++);
        if (rc) {
            printf("Inserted: %s (Code=%d)\n", insertIDs[i], codeVal - 1);
        }
        // If rc=0, an error message was already printed
    }

    // Print after insertions
    printf("\n=== STRUCTURE AFTER INSERTIONS ===\n");
    PrintObjects(pStruct4);

    // 4) Remove in the same order
    printf("\n=== REMOVING OBJECTS IN THE SAME ORDER ===\n");
    codeVal = 100;
    for (int i = 0; i < nInserts; i++) {
        Object2* pRemoved = RemoveExistingObject(&pStruct4, (char*)insertIDs[i]);
        if (pRemoved) {
            printf("Removed: %s %lu\n", pRemoved->pID, pRemoved->Code);
            // free the object
            free(pRemoved->pID);
            free(pRemoved->pTime1);
            free(pRemoved);
        }
        // otherwise error message was printed
    }

    // Print after removals
    printf("\n=== STRUCTURE AFTER REMOVALS ===\n");
    PrintObjects(pStruct4);

    // 5) Create a BST from the final structure
    printf("\n=== CREATING BST FROM FINAL STRUCTURE ===\n");
    Node* bstRoot = CreateBinaryTree(pStruct4);
    if (!bstRoot) {
        printf("BST is empty or creation failed.\n");
        return 0;
    }

    // 6) Traverse the BST (inorder)
    printf("\n=== INORDER BST TRAVERSAL ===\n");
    TreeTraversal(bstRoot);

    // 7) Delete a node from the BST by code.
    //    If it doesn't exist, we'll see a message.
    unsigned long codeToDelete = 422218;
    printf("\n=== DELETING CODE=%lu FROM BST ===\n", codeToDelete);
    bstRoot = DeleteTreeNode(bstRoot, codeToDelete);

    // Traverse again
    printf("\n=== INORDER BST AFTER DELETE ===\n");
    TreeTraversal(bstRoot);

    return 0;
}*/

int main()
{// 1) N=35 => create the base structure
    HeaderC* pStruct4 = GetStruct4(2, 35);
    if (!pStruct4) {
        printf("Failed to create structure.\n");
        return 1;
    }

    // 2) Print the base structure
    printf("=== INITIAL STRUCTURE (N=35) ===\n");
    PrintObjects(pStruct4);

    // 3) Insert in specified order
    const char* insertIDs[] = {
        "Dx Gz", "Dx Ga", "Db Aa", "Dk Za", "Dr Wa",
        "Aa Aa", "Ab Ba", "Za Aa", "Za Ab", "Za Ba",
        "Wx Xa", "Wx Aa", "zb Kk", "Zc ca", "Dr Wa",
        "ZB kk", "Fa", "Fa_Fa"
    };
    int nInserts = (int)(sizeof(insertIDs) / sizeof(insertIDs[0]));

    printf("\n=== INSERTING OBJECTS ===\n");
    int codeVal = 100;
    for (int i = 0; i < nInserts; i++) {
        int rc = InsertNewObject(&pStruct4, (char*)insertIDs[i], codeVal++);
        if (rc) {
            printf("Inserted: %s (Code=%d)\n", insertIDs[i], codeVal - 1);
        }
        // If rc=0, an error message was already printed
    }

    // Print after insertions
    printf("\n=== STRUCTURE AFTER INSERTIONS ===\n");
    PrintObjects(pStruct4);

    // 4) Remove in the same order
    printf("\n=== REMOVING OBJECTS IN THE SAME ORDER ===\n");
    codeVal = 100;
    for (int i = 0; i < nInserts; i++) {
        Object2* pRemoved = RemoveExistingObject(&pStruct4, (char*)insertIDs[i]);
        if (pRemoved) {
            printf("Removed: %s %lu\n", pRemoved->pID, pRemoved->Code);
            // free the object
            free(pRemoved->pID);
            free(pRemoved->pTime1);
            free(pRemoved);
        }
        // otherwise error message was printed
    }

    // Print after removals
    printf("\n=== STRUCTURE AFTER REMOVALS ===\n");
    PrintObjects(pStruct4);
;

    
    // --------------------------------------------------------
    // 12.2 (3) Create BST, print all nodes
    // --------------------------------------------------------
    printf("\n=== STEP 3: CREATE BST FROM N=35 AND TRAVERSE ===\n");
    Node* bstRoot1 = CreateBinaryTree(pStruct4);

    printf("\nINORDER TRAVERSAL (BST with N=35):\n");
    TreeTraversal(bstRoot1);
    


    // --------------------------------------------------------
    // 12.2 (4) Remove the BST's root, then print again
    // --------------------------------------------------------
    if (bstRoot1) {
        unsigned long rootCode = ((Object2*)bstRoot1->pObject)->Code;
        printf("\nRemoving BST root (Code=%lu)...\n", rootCode);

        bstRoot1 = DeleteTreeNode(bstRoot1, rootCode);

        printf("\nINORDER AFTER REMOVING OLD ROOT:\n");
        TreeTraversal(bstRoot1);
    }
   

    // --------------------------------------------------------
    // 12.2 (5) N=10
    // --------------------------------------------------------
    HeaderC* pStruct4_10 = GetStruct4(2, 10);
    if (!pStruct4_10) {
        printf("Error: failed to create structure (N=10).\n");
        return 1;
    }

    // --------------------------------------------------------
    // 12.2 (6) Print the structure for N=10
    // --------------------------------------------------------
    printf("\n=== STEP 6: STRUCTURE WITH N=10 ===\n");
    PrintObjects(pStruct4_10);

    // --------------------------------------------------------
    // 12.2 (7) Create BST and print (inorder)
    // --------------------------------------------------------
    printf("\n=== STEP 7: CREATE BST FROM N=10 AND TRAVERSE ===\n");
    Node* bstRoot2 = CreateBinaryTree(pStruct4_10);

    printf("\nINORDER TRAVERSAL (BST with N=10):\n");
    TreeTraversal(bstRoot2);


    // --------------------------------------------------------
    // 12.2 (9) Remove chosen keys from the BST, then print
    // --------------------------------------------------------
    // Adjust these to whatever codes is in BST.
    printf("\n=== STEP 9: REMOVING SELECTED KEYS FROM BST 258186307 ===\n");
    bstRoot2 = DeleteTreeNode(bstRoot2, 258186307);  // example
    bstRoot2 = DeleteTreeNode(bstRoot2, 105);  // example

    printf("\nINORDER AFTER REMOVING 101, 105:\n");
    TreeTraversal(bstRoot2);

    // --------------------------------------------------------
    // 12.2 (10) Remove a code that doesn't exist
    // --------------------------------------------------------
    printf("\n=== STEP 10: REMOVING NON-EXISTENT CODE=999999 ===\n");
    bstRoot2 = DeleteTreeNode(bstRoot2, 999999);

    printf("\nINORDER AFTER ATTEMPTED REMOVE OF CODE=999999:\n");
    TreeTraversal(bstRoot2);

    printf("\n=== END OF 12.2 TESTS ===\n");
    return 0;
}