#include<stdio.h>
#include <stdlib.h>
struct node{
    struct node *left;
    struct node *right;
    int data;
};

struct node *createNode(int value) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = value;
	newNode->left = NULL;
    newNode -> right = NULL;
	return newNode;
}
struct node *insert(struct node *root,int val){
    if(root == NULL){
        return createNode(val);
    }
    if(val < root -> data){
        root -> left = insert(root -> left,val);
    }
    else if(val > root -> data){
        root ->right = insert(root -> right,val);
    }
    return root;

}

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