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
    struct timeval start, stop;
    struct timeval startInside, stopInside;
    
    FILE *testingSHQ;

    testingSHQ = fopen("TestingSH.dat", "w");
    

    
  /*  if(argc < 2) {
        printf("usage: bench <integer>\n");
        exit(1);
    }
  
    
    int k = atoi(argv[1]);
    
    printf("# Queue size from 1 to %d\n", k);
   */

    //ORIGINAL FOR LOOP - CHANGED BT KATA
    //for(int s = 50; s < 10000; s= s+50) {
    for(int s = 50; s < 10000; s= s+50) {
        
        struct  SkewHeap*   newHeap = NewHeap();
     
     
        
        // intialize the Queue
        for (int i = 1 ; i <= s; i++)
        {
            double r= (double)rand() / (double)(RAND_MAX);
            double value= 2*r;
            enqueueT(value, newHeap);


            
        }
    
        




        
        for (int j = 1 ; j <= 10; j++)
        {

           //generate number between 1 and 50
           int randomevent= rand()%50 ;

            gettimeofday(&start, NULL);
            // dequeue an element
            
            double  oldValue=dequeueT(newHeap);
            
            
            
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
                
                enqueueT(newEvent[e], newHeap);
                s++;
            }
            
            
        
      
        gettimeofday(&stop, NULL);
        
        
        int time = stop.tv_sec - start.tv_sec;
        
        int s_remove=stopInside.tv_sec- startInside.tv_sec;
        int u = stop.tv_usec - start.tv_usec;
        int u_remove = stopInside.tv_usec - startInside.tv_usec;
        int t = (time*1000000+u)- (s_remove*1000000+u_remove);
        //per operation
        int perOperationTime= t/(5*s);

        
        //printf("Number of Q =  %d Time it takes is = %d\n", s, averagetime);
        //s = size of the queue , t = time for s*5 enqueue operations for queue size s
         fprintf(testingSHQ, "%d %d %f\n", s, t, 0.5);
       }     
   
    }

    
    
    return 0;
}
