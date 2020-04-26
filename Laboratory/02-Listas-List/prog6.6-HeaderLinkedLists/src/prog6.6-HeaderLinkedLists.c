/*
 ============================================================================
 Name        : 6-HeaderLinkedLists.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : 5. Write a program to implement a header linked list.
 ============================================================================
 */

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

struct node {
	int data;
	struct node *next;
};

struct node *start = NULL;
struct node* create_hll(struct node*);
struct node* display(struct node*);


int main() {
	int option;
	system("cls");
	do {
		printf("\n\n *****MAIN MENU *****");
		printf("\n 1: Create a list");
		printf("\n 2: Display the list");
		printf("\n 3: EXIT");
		printf("\n Enter your option : ");
		scanf("%d", &option);
		switch (option) {
		case 1:
			start = create_hll(start);
			printf("\n HEADER LINKED LIST CREATED");
			break;
		case 2:
			start = display(start);
			break;
		}
	} while (option != 3);
	getch();
	return 0;
}
struct node* create_hll(struct node *start) {
	struct node *new_node, *ptr;
	int num;
	printf("\n Enter -1 to end");
	printf("\n Enter the data : ");
	scanf("%d", &num);
	while (num != -1) {
		new_node = (struct node*) malloc(sizeof(struct node));
		new_node->data = num;
		new_node->next = NULL;
		if (start == NULL) {
			start = (struct node*) malloc(sizeof(struct node));
			start->next = new_node;
		} else {
			ptr = start;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new_node;
		}
		printf("\n Enter the data : ");
		scanf("%d", &num);
	}
	return start;
}
struct node* display(struct node *start) {
	struct node *ptr;
	ptr = start;
	while (ptr != NULL) {
		printf("\t %d", ptr->data);
		ptr = ptr->next;
	}
	return start;
}

/*
 Output
 ***** MAIN MENU *****
 1: Create a list
 2: Display the list
 3: EXIT
 Enter your option : 1
 Enter -1 to end
 */
