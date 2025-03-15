

#include "Headers.h"
#include "Objects.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Structs.h"

HeaderC* GetStruct4(int ObjectType, int nObjects) {
    HeaderC* pStruct4 = (HeaderC*)malloc(sizeof(HeaderC));
    if (!pStruct4) return NULL;

    pStruct4->ppObjects = (void**)calloc(26, sizeof(void*));
    pStruct4->cBegin = 'A';
    pStruct4->pNext = NULL;

    for (int i = 0; i < nObjects; i++) {
        char id[10];
        sprintf(id, "Object%d", i + 1);
        InsertNewObject(&pStruct4, id, i + 100);
    }

    return pStruct4;
}

void PrintObjects(HeaderC* pStruct4) {
    while (pStruct4) {
        printf("HeaderC cBegin: %c\n", pStruct4->cBegin);
        for (int i = 0; i < 26; i++) {
            Object2* pObj = (Object2*)pStruct4->ppObjects[i];
            while (pObj) {
                printf("  %s %lu %02d:%02d:%02d\n", pObj->pID, pObj->Code,
                    pObj->pTime1->Hour, pObj->pTime1->Minute, pObj->pTime1->Second);
                pObj = pObj->pNext;
            }
        }
        pStruct4 = pStruct4->pNext;
    }
}

int InsertNewObject(HeaderC** pStruct4, char* pNewID, int NewCode) {
    if (!pNewID || strlen(pNewID) < 1 || !(*pStruct4)) return 0;

    char cBegin = pNewID[0];
    HeaderC* current = *pStruct4, * prev = NULL;

    while (current && current->cBegin < cBegin) {
        prev = current;
        current = current->pNext;
    }
    if (!current || current->cBegin != cBegin) {
        HeaderC* newHeader = (HeaderC*)malloc(sizeof(HeaderC));
        newHeader->cBegin = cBegin;
        newHeader->ppObjects = (void**)calloc(26, sizeof(void*));
        newHeader->pNext = current;
        if (prev) prev->pNext = newHeader;
        else *pStruct4 = newHeader;
        current = newHeader;
    }

    int index = pNewID[1] - 'a';
    Object2* newObj = (Object2*)malloc(sizeof(Object2));
    newObj->pID = strdup(pNewID);
    newObj->Code = NewCode;
    newObj->pTime1 = (Time1*)malloc(sizeof(Time1));
    time_t rawTime;
    time(&rawTime);
    struct tm* timeInfo = localtime(&rawTime);
    newObj->pTime1->Hour = timeInfo->tm_hour;
    newObj->pTime1->Minute = timeInfo->tm_min;
    newObj->pTime1->Second = timeInfo->tm_sec;

    newObj->pNext = (Object2*)current->ppObjects[index];
    current->ppObjects[index] = newObj;
    return 1;
}

Object2* RemoveExistingObject(HeaderC** pStruct4, char* pExistingID) {
    if (!pExistingID || !(*pStruct4)) return NULL;

    char cBegin = pExistingID[0];
    HeaderC* current = *pStruct4, * prev = NULL;

    while (current && current->cBegin != cBegin) {
        prev = current;
        current = current->pNext;
    }
    if (!current) return NULL;

    int index = pExistingID[1] - 'a';
    Object2* prevObj = NULL, * currObj = (Object2*)current->ppObjects[index];

    while (currObj && strcmp(currObj->pID, pExistingID) != 0) {
        prevObj = currObj;
        currObj = currObj->pNext;
    }
    if (!currObj) return NULL;

    if (prevObj) prevObj->pNext = currObj->pNext;
    else current->ppObjects[index] = currObj->pNext;

    return currObj;
}

Node* CreateBinaryTree(HeaderC* pStruct4) {
    Node* root = NULL;

    while (pStruct4) {
        for (int i = 0; i < 26; i++) {
            Object2* pObj = (Object2*)pStruct4->ppObjects[i];
            while (pObj) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->pObject = pObj;
                newNode->pLeft = newNode->pRight = NULL;

                if (!root) root = newNode;
                else {
                    Node* curr = root, * prev = NULL;
                    while (curr) {
                        prev = curr;
                        curr = ((Object2*)curr->pObject)->Code > pObj->Code ? curr->pLeft : curr->pRight;
                    }
                    if (((Object2*)prev->pObject)->Code > pObj->Code) prev->pLeft = newNode;
                    else prev->pRight = newNode;
                }
                pObj = pObj->pNext;
            }
        }
        pStruct4 = pStruct4->pNext;
    }
    return root;
}

void TreeTraversal(Node* pTree) {
    if (!pTree) return;
    TreeTraversal(pTree->pLeft);
    Object2* pObj = (Object2*)pTree->pObject;
    printf("  %s %lu\n", pObj->pID, pObj->Code);
    TreeTraversal(pTree->pRight);
}

Node* DeleteTreeNode(Node* pTree, unsigned long int Code) {
    // Stub for simplicity
    return pTree;
}