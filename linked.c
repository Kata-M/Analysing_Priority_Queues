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
int size; //size of the list

struct Node* NewNode(int x){
	struct Node* newNode =  (struct Node*)malloc(sizeof(struct Node));
	newNode -> data = x;
	newNode -> front = NULL;
	newNode -> next = NULL; 
	return newNode;
}

//enqueue complexity O(n)
void Enqueue(int x){
		printf("\n \n");
		printf("New Enque operation: \n");
		//create a new node with the value of x
		struct Node* newNode = NewNode(x);
		//if the list is empty do this
		if(max == NULL){
			max = newNode;
			min = max;
			size++;
			return;
		}
		//-------------------------------------------------------------------------------//
		//insert to front if new is greater than or equal max. max always has the highest value
		//equality is to make the code stable. no swapping of equal values
		if(newNode->data >= max->data){
		max -> front = newNode;
		newNode -> next = max;
		max = newNode;
		newNode -> front = NULL;
		size++;
		return;
		}
		//-------------------------------------------------------------------------------//
		//insert to end if new is smaller than or equal min. min always has the smallest value
		//equality is to make the code stable. no swapping of equal values
		if(newNode->data <= min->data){
		min-> next = newNode;
		newNode -> front = min;
		min = newNode;
		newNode -> next = NULL;
		size++;
		return;
		}
		//-------------------------------------------------------------------------------//
		//compute the value of mid
		mid = (max->data + min->data)/2;
		printf("MID: %d\n", mid);
		if(newNode->data >= mid){
			//insert from the front (max)
				printf("INSERT FROM FRONT\n");

				struct Node* temp = max;
				while(newNode->data < temp->data && temp->next != NULL){
					temp = temp -> next;
				}
				    printf("new node: %d\n", newNode->data);
					printf("final temp: %d\n", temp->data);
					printf("max: %d\n", max->data);
					printf("min: %d\n", min->data);


					if(newNode->data >= temp->data){
						printf("Inside IF\n");
						temp->front->next = newNode;
						newNode->next = temp;
						newNode->front = temp->front;
						temp->front = newNode;
						size++;
				    }

		}else{
			//insert from the end (min)
				printf("INSERT FROM END");
				struct Node* temp = min;
				while(newNode->data > temp->data && temp->next != NULL){
					temp = temp -> front;
				}
				    printf("new node: %d\n", newNode->data);
					printf("final temp: %d\n", temp->data);
					printf("max: %d\n", max->data);
					printf("min: %d\n", min->data);

					if(newNode->data >= temp->data){
						printf("Inside IF\n");
						temp->front->next = newNode;
						newNode->next = temp;
						newNode->front = temp->front;
						temp->front = newNode;
						size++;
				    }
		}
}

//dequeue complexity O(1)
//dequeue returns the min element
int Dequeue(){
			if(max == NULL){
				printf("List is empty!\n");
				return 0;
			}
			int value = min->data;
			struct Node* temp;
			temp = min;
			min = temp->front;
			free(temp);
			if(min != NULL){
				min->next = NULL;
				size--;
			}
			if(size == 0){
				max =NULL;
			}
			//only one element left in the list
			if(max->next == NULL){
				value = max->data;
				max = NULL;
				size--;
			}
			printf("Dequeued value is  [%d].\n\n",value);
			return value;
}

void Print(){
	
	if(size != 0){
		struct Node* temp = max;

		printf("The linked list: ");
		while(temp != NULL){
			printf("[%d]->", temp->data);
			temp = temp->next;
		}
	}else{
		printf("The list is empty!");
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
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();
	Dequeue();
	Print();


}























