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

struct Node* max; //global pointer to the max node
struct Node* min; //global pointer to the min node
int mid; //average of max and min, decides if enque from front or end


struct Node* NewNode(int x){
	struct Node* newNode =  (struct Node*)malloc(sizeof(struct Node));
	newNode -> data = x;
	newNode -> front = NULL;
	newNode -> next = NULL; 

	return newNode;
}

void Enqueue(int x){
	//create a new node with the value of x
	struct Node* newNode = NewNode(x);
	//if the list is empty do this
	if(max == NULL){
		max = newNode;
		min = max;
		return;
	}
	//insert to front if new is greater than or equal max. max always has the highest value
	//equality is to make the code stable. no swapping of equal values
	if(newNode->data >= max->data){
	max -> front = newNode;
	newNode -> next = max;
	max = newNode;
	newNode -> front = NULL;
	return;
	}

	//insert to end if new is smaller than or equal min. min always has the smallest value
	//equality is to make the code stable. no swapping of equal values
	if(newNode->data <= min->data){
	min-> next = newNode;
	newNode -> front = min;
	min = newNode;
	newNode -> next = NULL;
	return;
	}

	mid = (max->data + min->data)/2;
	printf("MID: %d\n", mid);
	if(newNode->data >= mid){
		//insert from the front (max)
			printf("INSERT FROM FRONT");

			struct Node* temp = max;
			while(newNode->data < temp->data && temp->next != NULL){
				//if(newNode->data == temp->data) break;

				temp = temp -> next;
				//printf("WHILE temp: %d\n", temp->data);
			}
			    printf("new node: %d\n", newNode->data);
				printf("final temp: %d\n", temp->data);
				//printf("final temp front next: %d\n", temp->front->next->data);
				printf("max: %d\n", max->data);
				printf("min: %d\n", min->data);
	


				if(newNode->data >= temp->data){
					printf("Inside IF\n");

					temp->front->next = newNode;
					//printf("final temp front next: %d\n", temp->front->next->data);

					newNode->next = temp;
					//printf("newNode next: %d\n", newNode->next->data);

					newNode->front = temp->front;
					//printf("newNode front: %d\n", newNode->front->data);

					temp->front = newNode;
					//printf("temp front: %d\n", temp->front->data);
			
					//printf("\n");
			    }

	}else{
		//insert from the end (min)
			printf("INSERT FROM END");
			struct Node* temp = min;
			while(newNode->data > temp->data && temp->next != NULL){
				//if(newNode->data == temp->data) break;

				temp = temp -> front;
				//printf("WHILE temp: %d\n", temp->data);
			}
			    printf("new node: %d\n", newNode->data);
				printf("final temp: %d\n", temp->data);
				//printf("final temp front next: %d\n", temp->front->next->data);
				printf("max: %d\n", max->data);
				printf("min: %d\n", min->data);
				printf("\n");


				if(newNode->data >= temp->data){
					printf("Inside IF\n");

					temp->front->next = newNode;
					//printf("final temp front next: %d\n", temp->front->next->data);

					newNode->next = temp;
					//printf("newNode next: %d\n", newNode->next->data);

					newNode->front = temp->front;
					//printf("newNode front: %d\n", newNode->front->data);

					temp->front = newNode;
					//printf("temp front: %d\n", temp->front->data);
			
					//printf("\n");
			    }
	}
}

//insert_end is not used atm and should not be used
/*void Insert_End(int x){
	struct Node* newNode = NewNode(x);
	//if the list is empty
	if(max == NULL){
		max = newNode;
		min = max;
		return;
	}
	//if min does not point to anything yet
	if(min == NULL){
		max -> next = newNode;
		newNode->front = max;
		return;
	}
	newNode->front = min;
	min->next = newNode;
	min = newNode;
	newNode->next = NULL;
}*/

void Print(){
	struct Node* temp = max;
	printf("The linked list: ");
	while(temp != NULL){
		printf("[%d] -> ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	max = NULL;
	Print();
	Enqueue(4);
	Print();
	Enqueue(8);
	Print();
	Enqueue(2);
	Print();
	Enqueue(0);
	Print();
	Enqueue(1);
	Print();
	Enqueue(7);
	Print();
	Enqueue(0);
	Print();
	Enqueue(0);
	Print();
	Enqueue(0);
	Print();
	Enqueue(8);
	Print();
	Enqueue(4);
	Print();
	Enqueue(4);
	Print();
	/*
	Enqueue(1);
	Enqueue(3);
	Enqueue(2);
	Enqueue(0);
	Enqueue(6);
	*/

	Print();
	Print();

	printf("max: %d\n",max->data);	
	printf("min: %d\n",min->data);

}























