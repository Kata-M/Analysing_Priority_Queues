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
    

    double randEventsBest[1000];
    double randEventsWorst[1000];
    double randEvents[1000];
    clock_t start, end;
    double time;
    
        for (int i = 1 ; i <= 1000; i++)
        {
            double r= (double)rand() / (double)(RAND_MAX);
            double value=2*r;
            printf("Random: %f \n", value);
            randEventsBest[i] = value;
            randEventsWorst[i] = value;
            randEvents[i] = value;
        }




        for (int i = 0; i < 1000; i++)                     //Loop for ascending ordering
        {
            for (int j = 0; j < 1000; j++)             //Loop for comparing other values
            {
                 if (randEventsBest[j] > randEventsBest[i])                //Comparing other array elements
                {
                     double tmp = randEventsBest[i];         //Using temporary variable for storing last value
                     randEventsBest[i] = randEventsBest[j];            //replacing value
                     randEventsBest[j] = tmp;             //storing last value
                }  
            }
         }
        /* printf("\n\nAscending : ");                     //Printing message
         for (int i = 0; i < 1000; i++)                     //Loop for printing array data after sorting
         {
                printf(" %f \n", randEventsBest[i]);
        }
        */
         /*
         printf("\n\n randEvents: ");                     //Printing message
         for (int i = 0; i < 1000; i++)                     //Loop for printing array data after sorting
         {
                printf(" %f \n", randEvents[i]);
        }
        */



    FILE *testingQLL;
    
    testingQLL = fopen("TestingLL.dat", "w");
    
    for(int size = 50; size < 1000; size= size+50) {
        
        
        Create_Queue();
        
        
        // intialize the Queue
        for (int i = 1 ; i <= size; i++)
        {
            double value= randEvents[i];
            Enqueue(value);    
        }
        

        double newEvent;
        start = clock();
        for (int j = 1 ; j <= 50; j++){
                Dequeue();
                Enqueue(randEvents[size+j]);
        }
        end = clock();
        time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("Number of Q =  %d Time it takes is = %f\n", size, time);
        
        fprintf(testingQLL, "%d %f\n", size, time);
        
        
    }
    return 0;
}
