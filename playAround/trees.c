#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct node {
	struct node *left;
	struct node *right;
	int data;
};

struct node *createNode(int value) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
struct node *insert(struct node *root, int val) {
	if (root == NULL) {
		return createNode(val);
	}
	if (val < root->data) {
		root->left = insert(root->left, val);
	} else if (val > root->data) {
		root->right = insert(root->right, val);
	}
	return root;
}

void printPreorder(struct node *node) {
	if (node == NULL)
		return;

	/* first print data of node */
	printf("%d ", node->data);

	/* then recur on left subtree */
	printPreorder(node->left);

	/* now recur on right subtree */
	printPreorder(node->right);
}

void printInOrder(struct node *node) {
	if (node == NULL)
		return;
	printInOrder(node->left);
	printf("%d ", node->data);
	printInOrder(node->right);
}

void printPostorder(struct node *node) {
	if (node == NULL)
		return;

	// first recur on left subtree
	printPostorder(node->left);

	// then recur on right subtree
	printPostorder(node->right);

	// now deal with the node
	printf("%d ", node->data);
}

void printDataInRange(struct node *root, int low, int high) {
	/* base case */
	if (NULL == root)
		return;

	/* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
	if (low < root->data)
		printDataInRange(root->left, low, high);

	/* if root's data lies in range, then prints root's data */
	if (low <= root->data && high >= root->data)
		printf("%d\n", root->data);

	if (high > root->data)
		printDataInRange(root->right, low, high);
}

int TreeNumNodes(struct node *t) {
	if (t == NULL)
		return 0;
	else
		return 1 + TreeNumNodes(t->left) + TreeNumNodes(t->right);
}

struct node *rotateRight(struct node *n1) {
	if (n1 == NULL || n1->left == NULL)
		return n1;
	struct node *n2 = n1->left;
	n1->left = n2->right;
	n2->right = n1;
	return n2;
}

struct node *rotateLeft(struct node *n2) {
	if (n2 == NULL || n2->right == NULL)
		return n2;
	struct node *n1 = n2->right;
	n2->right = n1->left;
	n1->left = n2;
	return n1;
}

struct node *partition(struct node *t, int i) {
	if (t != NULL) {
		assert(0 <= i && i < TreeNumNodes(t));
		int m = TreeNumNodes(t->left);
		if (i < m) {
			t->left = partition(t->left, i);
			t = rotateRight(t);
		} else if (i > m) {
			t->right = partition(t->right, i - m - 1);
			t = rotateLeft(t);
		}
	}
	return t;
}
int findMinforN(struct node* root, int N)
{
    // If leaf node reached and is smaller than N
    if (root == NULL)
        return -1;
 
    // If node's value is greater than N and left value
    // is NULL or smaller then return the node value
    // if ((root->data >= N && root->left == NULL)
    //     || (root->data >= N && root->left->data < N))
    //     return root->data;
	if(root -> data >= N){
		if(root -> left == NULL || root->left->data < N)
			return root->data;
	}
 
    // if node value is smaller than N search in the
    // right subtree
    if (root->data <= N)
        return findMinforN(root->right, N);
 
    // if node value is greater than N search in the
    // left subtree
    else
        return findMinforN(root->left, N);
}
int main() {
	struct node *t = createNode(20);
	t = insert(t, 30);
	t = insert(t, 70);
	t = insert(t, 20);
	t = insert(t, 25);
	t = insert(t, 65);
	t = insert(t,80);
	t = insert(t,76);
	t = insert(t,90);
	t = insert(t,85);

	printf("%d\n",findMinforN(t,28));
	printInOrder(t);

}