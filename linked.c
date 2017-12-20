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
struct Node* middle;


struct Node* NewNode(int x){
	struct Node* newNode =  (struct Node*)malloc(sizeof(struct Node));
	newNode -> data = x;
	newNode -> front = NULL;
	newNode -> next = NULL; 

	return newNode;
}

void Insert_Front(int x){
	struct Node* newNode = NewNode(x);
	//if the list is empty do this
	if(first == NULL){
		first = newNode;
		last = first;
		return;
	}

	//insert to front if new is greater than or equal first. first always has the highest value
	//equality is to make the code stable. no swapping of equal values
	if(newNode->data > first->data){
	first -> front = newNode;
	newNode -> next = first;
	first = newNode;
	newNode -> front = NULL;
	return;
	}

	//insert to end if new is smaller than or equal last. last always has the smallest value
	//equality is to make the code stable. no swapping of equal values
	if(newNode->data < last->data){
	last-> next = newNode;
	newNode -> front = last;
	last = newNode;
	newNode -> next = NULL;
	return;
	}

	struct Node* temp = first;
	while(newNode->data <= temp->data && temp->next != NULL){
		//if(newNode->data == temp->data) break;

		temp = temp -> next;
		printf("WHILE temp: %d\n", temp->data);
	}
	    printf("new node: %d\n", newNode->data);
		printf("final temp: %d\n", temp->data);
		printf("final temp front next: %d\n", temp->front->next->data);
		printf("first: %d\n", first->data);
		printf("last: %d\n", last->data);
		printf("\n");


		if(newNode->data > temp->data){
			printf("Inside IF\n");

			temp->front->next = newNode;
			printf("final temp front next: %d\n", temp->front->next->data);

			newNode->next = temp;
			printf("newNode next: %d\n", newNode->next->data);

			newNode->front = temp->front;
			printf("newNode front: %d\n", newNode->front->data);

			temp->front = newNode;
			printf("temp front: %d\n", temp->front->data);
	
			printf("\n");
	    }





}

//insert_end is not used atm and should not be used
void Insert_End(int x){
	struct Node* newNode = NewNode(x);
	//if the list is empty
	if(first == NULL){
		first = newNode;
		last = first;
		return;
	}
	//if last does not point to anything yet
	if(last == NULL){
		first -> next = newNode;
		newNode->front = first;
		return;
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
	Insert_Front(1);
	Print();
	Insert_Front(3);
	Print();
	Insert_Front(2);
	Print();
	Insert_Front(5);
	Print();
	Insert_Front(3);
	Insert_Front(3);
	Insert_Front(0);

	Print();
	Print();

	printf("First: %d\n",first->data);	
	printf("Last: %d\n",last->data);

}























