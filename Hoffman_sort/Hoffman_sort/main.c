//
//  main.c
//  Hoffman_sort
//
//  Created by Change Cheng on 14/8/18.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

#include <stdio.h>
//const int num = 32;
//void Swap(int *x,int *y){
//    int temp;
//    temp = *x;
//    *x=*y;
//    *y=temp;
//    
//}
//void BubbleSort(int array[]){
//    for (int i=0; i<num-1; i++) {
//        for (int j=0; j<num-1-i; j++) {
//            //compare array[j] and array[j+1];
//            if (array[j]>array[j+1]) {
//                Swap(&array[j],&array[j+1]);
//            }
//        }
//    }
//}
const int MaxBit=16;
typedef struct {
    int bit[MaxBit];
    int start;
    
}HCodeType;

typedef struct {
    char name;
    int weight;
    int parent;
    int lchild;
    int rchild;
    
}HNodeType;  // def HNode
void initHNode(HNodeType *HuffNode,char name,int weight){
    HuffNode->name = name;
    HuffNode->weight= weight;
    HuffNode->parent=-1;
    HuffNode->lchild=-1;
    HuffNode->rchild=-1;
    
    
}
int main(int argc, const char * argv[]) {
    HNodeType *HuffNodeArray[5];
    initHNode(HuffNodeArray[0],'A',5);
    initHNode(HuffNodeArray[1],'B',4);
    initHNode(HuffNodeArray[2],'C',3);
    initHNode(HuffNodeArray[3],'D',2);
    initHNode(HuffNodeArray[4],'E',1);
    for (int i=0; i<5; i++) {
       // printf("%c",HuffNodeArray[i].name);
        printf("%d,%d,%d,%d\n",HuffNodeArray[i]->weight,HuffNodeArray[i]->parent,HuffNodeArray[i]->lchild,HuffNodeArray[i]->rchild);
    }
    
    
    printf("Hello, World!\n");
    return 0;
}
