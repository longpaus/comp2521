#include<stdio.h>
struct node{
    int data;
    struct node *next;
};
int sum(struct node *head){
    if(head == NULL)
        return 0;
    return head -> data + sum(head -> next);
}