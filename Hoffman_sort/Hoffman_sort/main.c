//
//  main.c
//  Hoffman_sort
//
//  Created by Change Cheng on 14/8/18.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

#include <stdio.h>

const int MaxBit=16;
//const int num=5;
typedef struct {
    int bit[MaxBit];
    int start;
    
}HCodeType;
//define a stack
typedef struct {
    int data[MaxBit];
    int length;
}Stack;
void initStack(Stack *st){
    st->length=0;
}
int emptyStack(Stack *st){
    if (st->length==0) {
        return 1;
    }
    return 0;
}
int fullStack(Stack *st) {
    if (st->length==MaxBit) {
        return 1;
    }
    return 0;
}
int pop(Stack *st){
    
    if (emptyStack(st)) {
        printf("Stack is empty!\n");
        return 0;
    }
    st->length--;
    return st->data[st->length];
}
void push(Stack *st,int n) {
    st->data[st->length]=n;
    st->length++;
    
}
int topStack(Stack *st){
    return st->data[st->length-1];
}
void clearStack(Stack *st){
    for (int i=0; i<st->length; i++) {
        pop(st);
    }
}
typedef struct {
    
    int weight;
    int parent;
    int lchild;
    int rchild;
    
}HNodeType;  // def HNode

//main   //
int main(int argc, const char * argv[]) {
    int num=5;
    HNodeType HuffmanTree[2*num-1];
    //symbols and weight
//    int weight[]={1,2,3,4,5};
    int weight[]={5,4,3,2,1};
    char name[]={'A','B','C','D','E'};
    //initialize HuffmanTree
//init 0~num-1
    for (int i=0; i<=num-1; i++) {
        HuffmanTree[i].weight= weight[i];
        HuffmanTree[i].parent=-1;
        HuffmanTree[i].lchild=-1;
        HuffmanTree[i].rchild=-1;
    }
//init num~2*num-1
    for (int i=num; i<2*num-1; i++) {
        HuffmanTree[i].weight= 0;
        HuffmanTree[i].parent=-1;
        HuffmanTree[i].lchild=-1;
        HuffmanTree[i].rchild=-1;
    }
    
//  print weight for test //
    
//    for (int i=0; i<2*num-1; i++) {
//        printf("weight is %d\n",HuffmanTree[i].weight);
//    }
    int i=0;
    int h1,h2;
    for (i=num; i<2*num-1; i++) {
//select two lowest weight node
        h1=0,h2=0;
        int m1=1000;
        int m2=1000;
        for (int j=0; j<=i-1; j++) {
            
            //select two node having lowest weight and no parent node
            if (HuffmanTree[j].parent==-1) {
//                printf("j is %d\n",j);
                if (HuffmanTree[j].weight<m1) {
                    m2=m1;
                    h2=h1;
                    h1=j;
                    m1=HuffmanTree[j].weight;
//                    printf("m1 is %d\n",m1);
    
                }else if(HuffmanTree[j].weight<m2){
                    h2=j;
                    m2=HuffmanTree[j].weight;
                }
            }
        }

//        printf("h1,h2 are %d,%d.\n",h1,h2);
//Update changed nodes//
        HuffmanTree[h1].parent=i;
        HuffmanTree[h2].parent=i;
        HuffmanTree[i].weight=HuffmanTree[h1].weight+HuffmanTree[h2].weight;
        HuffmanTree[h1].weight=0;   //lchild weight =0
        HuffmanTree[h2].weight=1;   //rchild weight =1
        HuffmanTree[i].lchild=h1;
        HuffmanTree[i].rchild=h2;
        
        
    }

    Stack code;   //code stack, store inversed code
    initStack(&code);
    
    for (int i=0; i<num; i++) {
        printf("Code of %c: ",name[i]);
        int j=i;
        
        while (HuffmanTree[j].parent!=-1) {

            push(&code, HuffmanTree[j].weight);
            j=HuffmanTree[j].parent;
        }
        //print code;
        while (!emptyStack(&code)) {
            printf("%d",pop(&code));
        }
        
        printf("\n");
    }
    
    return 0;
}







