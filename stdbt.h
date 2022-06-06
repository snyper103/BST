#ifndef STDBT_H_INCLUDED
#define STDBT_H_INCLUDED

typedef struct node* binTree;

short newRoot( binTree** root );
short newNode( binTree* node, long data );
short freeTree( binTree* root );

short isTreeEmpty( binTree* root );
long treesHeight( binTree* root );
long nodeCount( binTree* root );
long noLeafCount( binTree* root );
long leafCount( binTree* root );

short printPostOrder( binTree* root );
short printInOrder( binTree* root );
short printPreOrder( binTree* root );

short insertTree( binTree* root, long data );
short deleteNode( binTree* root, long data );
short treeQuery( binTree* root, long data );

short fprintPostOrder( const char* FILEname, binTree* root );
short fprintInOrder( const char* FILEname, binTree* root );
short fprintPreOrder( const char* FILEname, binTree* root );

short finsertTree( const char* FILEname, binTree* root );
short fdeleteNode( const char* FILEname, binTree* root );
short ftreeQuery( const char* queryFILEname, binTree* root, const char* answerFILEname );

#endif
