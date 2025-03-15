//
//            Structures: function prototypes
//            -------------------------------


void **GetStruct1(int ObjectType, int nObjects);
HeaderA *GetStruct2(int ObjectType, int nObjects);
HeaderB *GetStruct3(int ObjectType, int nObjects);
HeaderC *GetStruct4(int ObjectType, int nObjects);
HeaderA **GetStruct5(int ObjectType, int nObjects);
HeaderA *GetStruct6(int ObjectType, int nObjects);
HeaderD *GetStruct7(int ObjectType, int nObjects);

/* ObjectType - 1, 2,...10 - type of objects to be inserted into the data structure.
   nTypes -number of objects to be inserted into the data structure.
   ObjectType and nObjects are specified by the instructor.
   Return value - pointer to the first byte of data structure.
   
   Examples for structure from 25 objects of type 4:
   Object4 **pStruct1 = (Object4 **)GetStruct1(4, 25);
   HeaderA *pStruct2 = GetStruct2(4, 25);
   HeaderB *pStruct3 = GetStruct3(4, 25);
   HeaderC *pStruct4 = GetStruct4(4, 25);
   HeaderA **pStruct5 = GetStruct5(4, 25);
*/

// Prototypes for all functions in functions.cpp
int IsValidIDFormat(const char* pID);
int IsDuplicateID(HeaderC* pHead, const char* pID);
void PrintObjects(HeaderC* pStruct4);
int InsertNewObject(HeaderC** ppStruct4, char* pNewID, int NewCode);
Object2* RemoveExistingObject(HeaderC** ppStruct4, char* pExistingID);
Node* CreateBinaryTree(HeaderC* pStruct4);
void ProcessNode(Node* pNode);
void TreeTraversal(Node* pTree);
Node* DeleteTreeNode(Node* pTree, unsigned long int Code);