//
//  main.c
//  Skew heap
//
//  Created by kewser on 12/19/17.
//  Copyright © 2017 kewser All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include<stdlib.h>


struct SkewNode*  Merges (struct SkewNode* x,struct SkewNode* y);
//enqueue (double val,struct SkewHeap*  queues);
struct SkewHeap* NewHeap(void);
//struct SkewHeap* newHeap;

struct SkewNode {
    double value;
    struct SkewNode* left;
    struct SkewNode* right;
};
struct SkewNode* NewNode(double x){
    struct SkewNode* newNode =  (struct SkewNode*)malloc(sizeof(struct SkewNode));
    newNode -> value = x;
    newNode -> left = NULL;
    newNode -> right = NULL;
    
    return newNode;
}
struct SkewHeap {
    int size;
    struct SkewNode* root;
};
struct SkewHeap* NewHeap(){
    struct SkewHeap* newHeap=(struct SkewHeap*)malloc(sizeof(struct SkewHeap));
    newHeap -> size = 0;
    newHeap -> root = NULL;
    return newHeap;
};

void enqueueT (double val,struct SkewHeap*  queues){
    struct SkewNode* node= NewNode(val);
    struct SkewNode* roots =queues->root;
    queues->root = Merges(roots, node);
    queues->size++;
    
}
double dequeueT(struct SkewHeap*  queues)
{
    if (queues->root == NULL)
        return 0;
    double dequeElemnet=queues->root->value;
    queues->root = Merges(queues->root->left, queues->root->right);
    //double result= queues->root->value;
    /*printf("In dequeue!\n");
    printf("%f",result);
    printf("\n");*/
    queues-> size--;
    return dequeElemnet;
}

//struct SkewNode*  Merges (struct SkewNode* x,struct SkewNode* y);
struct SkewNode*  Merges (struct SkewNode* x,struct SkewNode* y){
   // printf("In Mrges!\n");
  
    if(x == NULL)
    {  //printf("One is null Mrges!\n");
        return y;}
    if(y == NULL)
    {   //printf("One is null Mrges!\n");
        return x;}
    if (x->value < y->value) {
       //printf("In Mrgesless!\n");
        struct SkewNode* temp = x->left;
        x->left = Merges(x->right, y);
        x->right = temp;
        return x;
    } else {
      //printf("In Mrgesgrete!\n");
        struct SkewNode* temp = y->right;
        y->right = Merges(y->left, x);
        y->left = temp;
        return y;
    }
    
}




int main(int argc, const char * argv[]) {

    FILE *fpdequeuT;
    FILE *fpenqueueT;
 
    fpdequeuT = fopen("dequeueT.dat", "w");
    fpenqueueT = fopen("enqueueT.txt", "w");
   double dequeuStimeT , dequeuEtimeT,enqueuStimeT,enqueuEtimeT , enqueutimeT,time6,enqueuetimeT,dequeutimeT,enqueuetimeL,dequeutimeL;
 
    //uniform [0.0,0.2]  ... 2rand()  ... 0.66 [jonas]
    srand(time(NULL));
    // the size of queues
    int sizeQueues =100;
    // for queuesize from 1- 1000
    for (int s=1 ; s < sizeQueues;s++){
        
    // intialze a new heap and fill it with given size s
     struct  SkewHeap*   newHeap = NewHeap();
        int randomevent= rand() % 10; //check it
       // double randomevent= 2*r;
        //printf("Initialze!\n");
        for (int i = 1 ; i <= s; i++)
        {
            double r= (double)rand() / (double)RAND_MAX;
            double value= 2*r;
            enqueueT(value, newHeap);
            
        }
       // Hold operation
       // printf("operation!\n");
        double  oldValue;
        for (int j = 1 ; j <= 5*s; j++)
        {
            //printf("insideoperation!\n");
            dequeuStimeT =clock();
            double  oldValue=dequeueT(newHeap);
            dequeuEtimeT =clock();
           //time it take to dequeue
            dequeutimeT= (dequeuEtimeT-dequeuStimeT)/CLOCKS_PER_SEC;
            fprintf(fpdequeuT, "%d, %f\n", s, dequeutimeT);
            //generate new events
            double newEvent[randomevent];
            for(int m=0; m < randomevent;m++)
            {
                newEvent[m]= oldValue+2*rand();
            }
            //time it take to enqueue
            for (int e=0; e<randomevent ;e++){
                 enqueuStimeT =clock();
                 enqueueT(newEvent[0], newHeap);
                 enqueuEtimeT =clock();
                 enqueutimeT= (enqueuEtimeT-enqueuStimeT)/CLOCKS_PER_SEC;
                fprintf(fpenqueueT, "%d, %f\n", s, enqueutimeT);
            }
          
         
        }
       
        
    }
    
 printf("Done\n");
 
    
 
    return 0;
}
