//

//  Skew heap
//
//  Created by kewser on 12/19/17.
//  Copyright © 2017 kewser All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>

struct SkewNode*  Merges (struct SkewNode* x,struct SkewNode* y);
struct SkewHeap* NewHeap(void);
struct SkewHeap* newHeap;

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
    //if (queues->root == NULL) // throw an exception
    double dequeElemnet=queues->root->value;
    queues->root = Merges(queues->root->left, queues->root->right);
    queues-> size--;
    return dequeElemnet;
}


struct SkewNode*  Merges (struct SkewNode* x,struct SkewNode* y){
  
  
    if(x == NULL)
    {
        return y;}
    if(y == NULL)
    {
        return x;}
    if (x->value < y->value) {
      
        struct SkewNode* temp = x->left;
        x->left = Merges(x->right, y);
        x->right = temp;
        return x;
    }
        struct SkewNode* temp = y->right;
        y->right = Merges(y->left, x);
        y->left = temp;
        return y;
    }
    
}




int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Welcome!\n");
    printf("Skewheap Test!\n");
    double result=0;

    newHeap = NewHeap();
    
    printf("Skewheap 4.0 added!\n");
    enqueueT(4.0, newHeap);
    printf("Skewheap 3.0 added!\n");
    enqueueT(3.0, newHeap);
    printf("Skewheap 8.0 added!\n");
    enqueueT(8.0, newHeap);
    printf("Skewheap 5.0 added!\n");
    enqueueT(5.0, newHeap);
    printf("Skewheap 3.0 dequeue!\n");
    result =dequeueT(newHeap);
    printf("%f",result);
    printf("\n");
    printf("Skewheap 2.0 added!\n");
    enqueueT(2.0, newHeap);
    printf("Skewheap 9.0 added!\n");
    enqueueT(9.0, newHeap);
    printf("Skewheap 2.0 dequeue!\n");
    result = dequeueT(newHeap);
    printf("%f",result);
    printf("\n");
    printf("Skewheap 4.0 dequeue!\n");
    result =dequeueT(newHeap);
    printf("%f",result);
    printf("\n");
    printf("Skewheap 5.0 dequeue!\n");
    result =dequeueT(newHeap);
    printf("%f",result);
    printf("\n");
    printf("Skewheap 1.0 added!\n");
    enqueueT(1.0, newHeap);
    printf("Skewheap 1.0 dequeue!\n");
    result =dequeueT(newHeap);
    printf("%f",result);
    printf("\n");
   
    
    return 0;
}

