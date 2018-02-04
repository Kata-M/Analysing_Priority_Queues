//
//  main.c
//  Testing_prioirity
//
//  Created by kuku_eri@yahoo.com on 1/19/18.
//  Copyright © 2018 kuku_eri@yahoo.com. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

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

    double randEvents[1800];
    clock_t start, end;
    double time;
    
        for (int i = 1 ; i <= 1800; i++)
        {
            double r= (double)rand() / (double)(RAND_MAX);
            double value=2*r;
            randEvents[i] = value;
        }

    FILE *testingSHQ;
    
    testingSHQ = fopen("TestingSH.dat", "w");
    

    for(int size = 50; size < 1800; size= size+50) {
        printf("Size: %d",size);
        
        struct  SkewHeap*   newHeap = NewHeap();
        double oldTime;

    for(int k = 0; k<50 ; k++){ 
        
        // intialize the Queue
        for (int i = 1 ; i <= size; i++)
        {
            enqueueT(randEvents[i+k], newHeap);  
        }
        

        double newEvent;


        start = clock();
        for (int j = 1 ; j <= 50; j++){
                dequeueT(newHeap);
                enqueueT(randEvents[size+j+k], newHeap);  

        }
        end = clock();
        time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
      //  printf("Number of Q =  %d Time it takes is = %f\n", size, time);
        oldTime = oldTime + time;

        fprintf(testingSHQ, "%d %f\n", size, time);

    }
    
    //average point
     fprintf(testingSHQ, "%d %f \n", size, oldTime/50);

        
        
    }
    return 0;
}
