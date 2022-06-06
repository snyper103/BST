#include "stdbt.h"
#include <stdio.h>
#include <stdlib.h>

/**< Just in the .c */
struct node
{
    long data;
    struct node* right;
    struct node* left;
};

void freeNode( binTree node )
{
    if ( !node )
        return;

    freeNode(node->left);
    freeNode(node->right);
    free(node);
    node = NULL;
}
binTree minValueNode( binTree node, binTree* previous )
{
    binTree current = node;

    while ( current->left )
    {
        *previous = current;
        current = current->left;
    }

    return current;
}
binTree maxValueNode( binTree node, binTree* previous )
{
    binTree current = node;

    while ( current->right )
    {
        *previous = current;
        current = current->right;
    }

    return current;
}
binTree searchNode( binTree node )
{
    binTree previous, current;

    if ( !node->left )
    {
        current = node->right;

        free(node);
        return current;
    }

    previous = node;
    if ( node->left )
        current = maxValueNode(node->left, &previous);

    else
        current = minValueNode(node->right, &previous);

    if ( previous->data != node->data )
    {
        previous->right = current->left;
        current->left = node->left;
    }

    current->right = node->right;
    free(node);
    return current;
}

/**< In the .h and .c */
short newRoot( binTree** root )
{
    *root = (binTree*)malloc(sizeof(binTree));

    if ( !root )
        return 0;

    **root = NULL;

    return 1;
}
short newNode( binTree* node, long data )
{
    *node = (binTree)malloc(sizeof(struct node));

    if ( !node )
        return 0;

    (*node)->data = data;
    (*node)->left = NULL;
    (*node)->right = NULL;

    return 1;
}
short freeTree( binTree* root )
{
    if ( !root )
        return 0;

    freeNode(*root);
    free(root);

    return 1;
}

short isTreeEmpty( binTree* root )
{
    return ( (!root) || ( !(*root) ) );
}
long treesHeight( binTree* root )
{
    long right_height = 0, left_height = 0;

    if ( isTreeEmpty(root) )
        return 0;

    left_height = treesHeight( &((*root)->left) );
    right_height = treesHeight( &((*root)->right) );

    if ( left_height > right_height )
        return left_height + 1;

    else
        return right_height + 1;
}
long nodeCount( binTree* root )
{
    if ( isTreeEmpty(root) )
        return 0;

    return nodeCount( &((*root)->left) ) + nodeCount( &((*root)->right) ) + 1;
}
long noLeafCount( binTree* root )
{
    if ( isTreeEmpty(root) )
        return 0;

    if ( (!(*root)->left) && (!(*root)->right) )
        return 0;

    return noLeafCount( &((*root)->left) ) + noLeafCount( &((*root)->right) ) + 1;
}
long leafCount( binTree* root )
{
    if ( isTreeEmpty(root) )
        return 0;

    if ( (!(*root)->left) && (!(*root)->right) )
        return 1;

    return leafCount( &((*root)->left) ) + leafCount( &((*root)->right) );
}

short printPostOrder( binTree* root )
{
    if ( isTreeEmpty(root) )
        return 0;

    printPostOrder( &((*root)->left) );
    printPostOrder( &((*root)->right) );

    printf("%li, ", (*root)->data);

    return 1;
}
short printInOrder( binTree* root )
{
    if ( isTreeEmpty(root) )
        return 0;

    printPostOrder( &((*root)->left) );

    printf("%li, ", (*root)->data);

    printPostOrder( &((*root)->right) );

    return 1;
}
short printPreOrder( binTree* root )
{
    if ( isTreeEmpty(root) )
        return 0;

    printf("%li, ", (*root)->data);

    printPostOrder( &((*root)->left) );
    printPostOrder( &((*root)->right) );

    return 1;
}

short insertTree( binTree* root, long data )
{
    short bol = 0;

    if ( !root )
        return 0;

    if ( !*root )
    {
        binTree node;
        bol = newNode(&node, data);

        if ( !bol )
            return 0;

        *root = node;

        return 1;
    }

    if ( data > (*root)->data )
        bol = insertTree( &((*root)->right), data );

    else
        if ( data < (*root)->data )
            bol = insertTree( &((*root)->left), data );

    return bol;
}
short deleteNode( binTree* root, long data )
{
    binTree previous = NULL, current = *root;
    short bol;

    if ( isTreeEmpty(&current) )
        return 0;

    if ( data == current->data )
    {
        if ( current->data == (*root)->data )
            *root = searchNode(current);

            else
            {
                if ( previous->right->data == current->data )
                    previous->right = searchNode(current);

                else
                    previous->left = searchNode(current);
            }

            return 1;
    }

    previous = current;
    if ( data > current->data )
            bol = deleteNode( &current->right, data );

    else
        bol = deleteNode( &current->left, data );

    return bol;
}
short treeQuery( binTree* root, long data )
{
    short bol = 0;

    if ( isTreeEmpty(root) )
        return 0;

    if ( data > (*root)->data )
        bol = treeQuery( &((*root)->right), data );

    else
    {
        if ( data < (*root)->data )
            bol = treeQuery( &((*root)->left), data );

        else
            return 1;
    }

    return bol;
}

short fprintPostOrder( const char* FILEname, binTree* root )
{
    FILE* fp = fopen(FILEname, "a+");

    if ( !fp )
        return 0;

    if ( isTreeEmpty(root) )
        return 0;

    printPostOrder( &((*root)->left) );
    printPostOrder( &((*root)->right) );

    fprintf(fp, "%li, ", (*root)->data);

    fclose(fp);
    return 1;
}
short fprintInOrder( const char* FILEname, binTree* root )
{
    FILE* fp = fopen(FILEname, "a+");

    if ( !fp )
        return 0;

    if ( isTreeEmpty(root) )
        return 0;

    printPostOrder( &((*root)->left) );

    fprintf(fp, "%li, ", (*root)->data);

    printPostOrder( &((*root)->right) );

    fclose(fp);
    return 1;
}
short fprintPreOrder( const char* FILEname, binTree* root )
{
    FILE* fp = fopen(FILEname, "a+");

    if ( !fp )
        return 0;

    if ( isTreeEmpty(root) )
        return 0;

    fprintf(fp, "%li, ", (*root)->data);

    printPostOrder( &((*root)->left) );
    printPostOrder( &((*root)->right) );

    fclose(fp);
    return 1;
}

short finsertTree( const char* FILEname, binTree* root )
{
    long data;
    short bol = 0;
    FILE* fp = fopen(FILEname, "r");

    if ( !fp )
        return 0;

    while ( (fscanf(fp, " %li %*s", &data)) != EOF )
        bol = insertTree(root, data);

    fclose(fp);
    return bol;
}
short fdeleteNode( const char* FILEname, binTree* root )
{
    long data;
    short bol = 0;
    FILE* fp = fopen(FILEname, "r");

    if ( !fp )
        return 0;

    while ( (fscanf(fp, " %li %*s", &data)) != EOF )
        bol = deleteNode(root, data);

    fclose(fp);
    return bol;
}
short ftreeQuery( const char* queryFILEname, binTree* root, const char* answerFILEname )
{
    long data;
    short bol = 0;
    FILE* query = fopen(queryFILEname, "r");
    FILE* answer = fopen(answerFILEname, "w+");

    if ( (!query) || (!answer) )
        return 0;

    while ( (fscanf(query, " %li %*s", &data)) != EOF )
    {
        bol = treeQuery(root, data);
        fprintf(answer, "%hi, ", bol);
    }

    fclose(query);
    fclose(answer);
    return 1;
}
