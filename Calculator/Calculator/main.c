//
//  main.c
//  Calculator
//
//  Created by Change Cheng on 14/8/16.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

#include <stdio.h>
const int Max=32;
typedef struct {
    int data[Max];
    
    int length;
    
} Stack;
void initStack(Stack st){
    st.length=0;
}
int emptyStack(Stack st){
    if (st.length==0) {
        return 1;
    }
    return 0;
}
int fullStack(Stack st) {
    if (st.length==Max) {
        return 1;
    }
    return 0;
}
int pop(Stack st){
    
    if (emptyStack(st)) {
        printf("Stack is empty!\n");
        return 0;
    }
    st.length--;
    return st.data[st.length];
}
void push(Stack st,int n) {
    st.data[st.length]=n;
    st.length++;
    
}
int topStack(Stack st){
    return st.data[st.length-1];
}
void clearStack(Stack st){
    for (int i=0; i<st.length; i++) {
        pop(st);
    }
}
int isOperator(int c) {
    if (c==40||c==41||c==42||c==43||c==45||c==47||c==35) {
        return 1;
    }
    return 0;
}
int isNum(int c){
    if (c>=48 && c<=57) {
        return 1;
    }
    return 0;
}
void ProcessString(int array[]){
    int c;
    int i=0;
    while ((c=getchar())!='\n') {
        //process char
        if (isNum(c)) {
            c=c-48;
            array[i]=c;
            i++;
        }else if (isOperator(c)){
            array[i]=c;
            i++;
        }
    }
    array[i]=35; //add # to end
}
int dect(int c){
    switch (c) {
        case 43:
            return 0;
            break;
        case 45:
            return 1;
            break;
        case 42:
            return 2;
            break;
        case 47:
            return 3;
            break;
        case 40:
            return 4;
            break;
        case 41:
            return 5;
            break;
        case 35:
            return 6;
            break;
        default:
            break;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    // priority
    int priority[7][7]={
    //   +,-,*,/,(,),#
    //  43,45,42,47,40,41,35
        {0,0,0,0,1,1,1},
        {0,0,0,0,1,1,1},
        {1,1,0,0,1,1,1},
        {1,1,0,0,1,1,1},
        {1,1,1,1,1,-1,1},
        {0,0,0,0,-1,2,1},
        {0,0,0,0,1,0,-1}
    
    };
    //conver symbol to choose priority
//    int n=dect(35);
//    printf("%d",n);
    int array[Max];
    int tempnum1,tempnum2;
    ProcessString(array);    //convert operation to number array
    for (int i=0; i<32; i++) {
        printf("%d,",array[i]);
    }
    //execute
    Stack operands,operators;
    push(operators, 35);//initialization
    for (int i=0; i<Max; i++) {
        if (array[i]>=0&&array[i]<=9) {
            //num into operands
            push(operands, array[i]);
        }else{
            //symbols into operators
            int lastop=topStack(operators);
            int prio=priority[dect(array[i])][dect(lastop)];
            switch (prio) {
                case 1:
                    push(operators, array[i]);
                    break;
                case 0:
                    //priority less than last operator
                    break;
                case -1:
                    //finish
                    break;
                case 2:
                    //error
                    printf("Your operation is wrong!\n");
                    break;
                default:
                    break;
            }
//            if (prio==1) {
//                push(operators, array[i]);
//            }else if (prio ==0){
//                //priority less than last operator
//            }else if () {
//                
//            }
//                
//            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    printf("Hello, World!\n");
    return 0;
}
