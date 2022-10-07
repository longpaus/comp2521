#include<stdio.h>
#include <stdlib.h>
struct node{
    struct node *left;
    struct node *right;
    int data;
};

void printPreorder(struct node* node)
{
    if (node == NULL)
        return;
 
    /* first print data of node */
    printf("%d ", node->data);
 
    /* then recur on left subtree */
    printPreorder(node->left);
 
    /* now recur on right subtree */
    printPreorder(node->right);
}

void printInOrder(struct node *node){
    if(node == NULL)
        return;
    printInOrder(node -> left);
    printf("%d ",node->data);
    printInOrder(node -> right);
}

void printPostorder(struct node* node)
{
    if (node == NULL)
        return;
 
    // first recur on left subtree
    printPostorder(node->left);
 
    // then recur on right subtree
    printPostorder(node->right);
 
    // now deal with the node
    printf("%d ", node->data);
}