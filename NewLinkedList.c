#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>


struct Node {
    double data;
    struct Node* front;
    struct Node* next;
};


struct Node* NewNode(double x){
    struct Node* newNode =  (struct Node*)malloc(sizeof(struct Node));
    newNode -> data = x;
    newNode -> front = NULL;
    newNode -> next = NULL;
    return newNode;
}

struct Node* max; //pointer to the max node
struct Node* min; //pointer to the min node
double mid; //average of max and min, decides if enque from front or end
int size; //size of the list


void Create_Queue(){
    max = NULL;
    return;
}
//enqueue complexity O(n)
void Enqueue(double x){
    //printf("\n \n");
    //printf("New Enque operation: \n");
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
   // printf("MID: %d\n", mid);
    if(newNode->data >= mid){
        //insert from the front (max)
       // printf("INSERT FROM FRONT\n");
        
        struct Node* temp = max;
        while(newNode->data < temp->data && temp->next != NULL){
            temp = temp -> next;
        }
      //  printf("new node: %d\n", newNode->data);
      //  printf("final temp: %d\n", temp->data);
      //  printf("max: %d\n", max->data);
      //  printf("min: %d\n", min->data);
        
        
        if(newNode->data >= temp->data){
           // printf("Inside IF\n");
            temp->front->next = newNode;
            newNode->next = temp;
            newNode->front = temp->front;
            temp->front = newNode;
            size++;
        }
        
    }else{
        //insert from the end (min)
        //printf("INSERT FROM END");
        struct Node* temp = min;
        while(newNode->data > temp->data && temp->next != NULL){
            temp = temp -> front;
        }
      //  printf("new node: %d\n", newNode->data);
      //  printf("final temp: %d\n", temp->data);
       // printf("max: %d\n", max->data);
      //  printf("min: %d\n", min->data);
        
        if(newNode->data >= temp->data){
            //printf("Inside IF\n");
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
double Dequeue(){
    if(max == NULL){
        //printf("List is empty!\n");
        return 0;
    }
    double value = min->data;
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
   // printf("Dequeued value is  [%d].\n\n",value);
    return value;
}

void Print(){
    
    if(size != 0){
        struct Node* temp = max;
        
        printf("The linked list: ");
        while(temp != NULL){
           // printf("[%d]->", temp->data);
            temp = temp->next;
        }
    }else{
        printf("The list is empty!");
    }
    printf("\n");
}

int main() {
    
    struct timeval start, stop;
    struct timeval startInside, stopInside;
    
    
    FILE *testingQLL;
    
    testingQLL = fopen("TestingLL.dat", "w");
    
    for(int s = 50; s < 500; s= s+50) {
        
        
        Create_Queue();
        
        
        // intialize the Queue
        for (int i = 1 ; i <= s; i++)
        {
            double r= (double)rand() / (double)(RAND_MAX);
            double value=2*r;
            Enqueue(value);
            
            
            
        }
        
        
        //generate number between 1 and 50
        int randomevent= rand()%50 ;
        
        gettimeofday(&start, NULL);
        
        for (int j = 1 ; j <= 5*s; j++)
        {
            // dequeue an element
            
           double  oldValue=Dequeue();
            
            
            
            gettimeofday(&startInside, NULL);
            //generate event of size randomevent and add the values
           double newEvent[randomevent];
            for(int m=0; m < randomevent;m++)
            {
               double r= (double)rand() / (double)RAND_MAX;
                newEvent[m]= oldValue+2*r;
            }
            gettimeofday(&stopInside, NULL);
            
            
            
            
            //time it take to enqueue a number of randomevent events
            for (int e=0; e<randomevent ;e++){
                
                
                Enqueue(newEvent[e]);
            }
            
            
        
        
        gettimeofday(&stop, NULL);
        
        
        int time = stop.tv_sec - start.tv_sec;
        
        int s_remove=stopInside.tv_sec- startInside.tv_sec;
        int u = stop.tv_usec - start.tv_usec;
        int u_remove = stopInside.tv_usec - startInside.tv_usec;
        int t = (time*1000000+u)- (s_remove*1000000+u_remove);
        //per operation
       // int averagetime= t/(5*s);
        
        printf("Number of Q =  %d Time it takes is = %d\n", s, t);
        
        fprintf(testingQLL, "%d, %d\n", s, t);
        
        }
    }
    
    
    
    return 0;
}


