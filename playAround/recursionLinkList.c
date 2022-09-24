#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};
struct node *createNode(int value, struct node *next) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = value;
	newNode->next = next;
	return newNode;
}

struct node *lastNode(struct node *head) {
	if (head == NULL || head->next == NULL)
		return head;
	return lastNode(head->next);
}

struct node *append(int value, struct node *head) {
	if (head == NULL)
		return createNode(value, NULL);
	head->next = append(value, head->next);
	return head;
}

int sum(struct node *head) {
	if (head == NULL)
		return 0;
	return head->data + sum(head->next);
}
void printList(struct node *head) {
	printf("%d\n", head->data);
	if (head->next == NULL)
		return;
	printList(head->next);
}

int length(struct node *head) {
	if (head == NULL)
		return 0;
	return 1 + length(head->next);
}

struct node *delete (int value, struct node *head) {
	if (head->data == value)
		return head->next;
	head->next = delete (value, head->next);
	return head;
}

//insert number in sorted list
struct node *insert(int val, struct node *head) {
	if (head == NULL||val <= head->data)
		return createNode(val, head);
	head->next = insert(val, head-> next);
	
	return head;
}
int main() {
	struct node *listA = NULL;
	
	listA = append(3,listA);
	listA = append(7,listA);
	listA = append(5,listA);
	listA = append(3,listA);
	listA = append(2,listA);

	struct node *listB = function(listA);
	printList(listB);
}