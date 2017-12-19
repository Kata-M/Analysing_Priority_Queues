/*double linked list structure*/
/*by Kata M*/
/*19.12.2017 Stockholm Sweden*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



struct Node {
	int data;
	struct Node* front;
	struct Node* next;
	
};

struct Node* first; //global pointer to the first node
struct Node* last; //global pointer to the last node


struct Node* NewNode(int x){
	struct Node* newNode =  (struct Node*)malloc(sizeof(struct Node));
	newNode -> data = x;
	newNode -> front = NULL;
	newNode -> next = NULL; 

	return newNode;
}

void Insert_Front(int x){
	struct Node* newNode = NewNode(x);
	if(first == NULL){
		first = newNode;
		return;
	}
	first -> front = newNode;
	newNode -> next = first;
	first = newNode;

}

void Insert_End(int x){
	struct Node* newNode = NewNode(x);
	if(first == NULL){
		first = newNode;
		return;
	}
	if(last == NULL){
		first -> next = newNode;
		newNode->front = first;
	}

	newNode->front = last;
	last->next = newNode;
	last = newNode;
	newNode->next = NULL;
}

void Print(){
	struct Node* temp = first;
	printf("The linked list: ");

	while(temp != NULL){
		printf("[%d] -> ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	first = NULL;
	struct Node* node = NewNode(1);
	printf("Node: %d\n",node->data);
	Print();
	Insert_Front(3);
	Print();
	Insert_Front(4);
	Print();
	Insert_Front(2);
	Print();
	Insert_Front(10);
	Print();
}























