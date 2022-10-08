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

void printDataInRange(struct node *root,int low,int high){
    /* base case */
   if ( NULL == root )
      return;
 
   /* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
   if ( low < root->data )
        printDataInRange(root->left, low, high);
 
   /* if root's data lies in range, then prints root's data */
   if ( low <= root->data && high >= root->data )
        printf("%d\n", root->data );
 
    if(high > root->data)
        printDataInRange(root->right, low, high);
}
int main(){
    struct node *t = createNode(8);
    t = insert(t,3);
    t = insert(t,10);
    t = insert(t,1);
    t = insert(t,6);
    t = insert(t,14);
    t = insert(t,13);
    t = insert(t,4);
    t = insert(t,7);

    printDataInRange(t,0,20);
}