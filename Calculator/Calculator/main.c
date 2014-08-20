//
//  main.c
//  Calculator
//
//  Created by Change Cheng on 14/8/16.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//(-48*(12-6)/-22+40)*-30        -1590
// (-628*1993/(6+13))/1993
//-45/5--5*8
// 11/0

//calculate integer calculation expression with float result
#include <stdio.h>
const int Max=64;      //most Max bits of expression
//def stack
typedef struct {
    float data[Max];
    int length;
    
} Stack;
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
    if (st->length==Max) {
        return 1;
    }
    return 0;
}
float pop(Stack *st){
    
    if (emptyStack(st)) {
        printf("Stack is empty!\n");
        return 0;
    }
    st->length--;
    return st->data[st->length];
}
void push(Stack *st,float n) {
    st->data[st->length]=n;
    st->length++;
    
}
float topStack(Stack *st){
    return st->data[st->length-1];
}
void clearStack(Stack *st){
    for (int i=0; i<st->length; i++) {
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

//process operation expression
void ProcessString(int array[],int opOrNum[]){
    //    int opOrNum[Max];//store tag of array
    int lastisop=0;
    int lastop=0;  //store last op
    int c=0;
    int lessThanZeroNum=0;
    int x=0;//num temp
    int tag=0;  //record whether there is a number input
    int i=0;
    while ((c=getchar())!='\n') {
        //process char
        if (isNum(c)) {
            c=c-48;
            x=10*x+c;
            tag=1;
            
        }else if (isOperator(c)){
            if (tag==1) {         //encounter an op,last input is a number
                array[i]=x;
                opOrNum[i]=0;    //0 means num
                lastisop=0;
                lessThanZeroNum=0;
                x=0;
                tag=0;
                i++;
            }
            //consider unary -
            if ((lastisop==1 && c==45 && lastop!=41 )|| (i==0&&c==45)) {   //last op should not be ')'
                //unary -
                lessThanZeroNum=1;
                array[i]=50;
                opOrNum[i]=1;
                i++;
                lastisop=1;
                lastop=50;      //use 50 as unary -
                
            }else{
                //not unary - normal operation
                array[i]=c;
                opOrNum[i]=1;       // 1 means op
                i++;
                lastisop=1;
                lastop=c;
            }
        }
    }
    if (tag==1) {
        array[i]=x;
        opOrNum[i]=0;
        i++;
        array[i]=35; //add # to end
        opOrNum[i]=1;
    }else{
        array[i]=35; //add # to end
        opOrNum[i]=1;
        
    }
}
//convert c to correspondent prior no.
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
        case 50:
            return 7;
            break;
        default:
            break;
    }
    return 0;
}


/////main
int main(int argc, const char * argv[]) {
    printf("@@@@@@@@@@ @@@@@@@ @@@   @@   @@    @@@@  \n");
    printf("      @@@  @@      @@@@  @@  @@@   @@   @ \n");
    printf("    @@@    @@@@@@  @@ @@ @@   @@     @@   \n");
    printf("  @@@      @@      @@  @@@@   @@   @   @@ \n");
    printf("@@@@@@@@@@ @@@@@@@ @@   @@@  @@@@   @@@@  \n");
    
    printf("Simple Calculator     made by Zen1s\n");
    printf("Please input your calculation expression: \n");
    
    // priority
    int priority[8][8]={
        //   +,-,*,/,(,),#,u
        //  43,45,42,47,40,41,35,50
        {0,0,0,0,1,1,1,0},
        {0,0,0,0,1,1,1,0},
        {1,1,0,0,1,1,1,0},
        {1,1,0,0,1,1,1,0},
        {1,1,1,1,1,-1,1,1},  // left ( is prior to unary -
        {0,0,0,0,-1,2,1,0},
        {0,0,0,0,1,0,3,0},
        {1,1,1,1,1,1,1,0}     //add unary -
        
    };
    
    int array[Max],opOrNum[Max];
    float tempnum1=0.0,tempnum2=0.0,tempsum=0.0;
    int tempop=0;
    ProcessString(array,opOrNum);    //convert operation to number array
    
    //execute
    Stack operands,operators;
    push(&operators, 35);//initialization
    int unfinished = 1;
    int errorTag=0;
    printf("\n");
    
    for (int i=0; i<Max&&unfinished; i++) {
        if (opOrNum[i]==0) {              //array[i]>=0&&array[i]<=9
            //num into operands
            push(&operands, (float)array[i]);
        }else{
            //symbols into operators
            int lastop=(int)topStack(&operators);
            int prio=priority[dect((int)array[i])][dect(lastop)];
            
            switch (prio) {
                case 1:
                    push(&operators, array[i]);
                    break;
                case 0:
                    //priority less than last operator
                    if (operands.length<1) {  //operands less than 2, error
                        printf("Error, you operation expression is wrong!!\n");
                        unfinished=0;
                        errorTag=1;
                    }else{
                        tempop=pop(&operators);
                        switch (tempop) {
                            case 43:
                                tempnum2 = pop(&operands);
                                tempnum1 = pop(&operands);
                                tempsum = tempnum1 + tempnum2;   //+
                                break;
                            case 45:
                                tempnum2 = pop(&operands);
                                tempnum1 = pop(&operands);
                                tempsum = tempnum1 - tempnum2;  //-
                                break;
                            case 42:
                                tempnum2 = pop(&operands);
                                tempnum1 = pop(&operands);
                                tempsum = tempnum1 * tempnum2;  //*
                                break;
                            case 47:
                                tempnum2 = pop(&operands);
                                tempnum1 = pop(&operands);
                                if (tempnum2==0) {
                                    //error
                                    printf("Error, 0 can't be divided!!\n");
                                    unfinished=0;
                                    errorTag=1;
                                }else{
                                    tempsum = tempnum1 / tempnum2;
                                }
                                break;
                            case 50:   //unary -
                                tempnum2 = pop(&operands);
                                tempsum = -tempnum2;
                                break;
                                
                            default:
                                break;
                        }
                        push(&operands,tempsum);
                        i--;
                    }
                    break;
                case -1:
                    // ==
                    pop(&operators);
                    break;
                case 3:
                    //finished
                    unfinished=0;
                    break;   //fcuk!! It cost me so much time to find this bug.
                case 2:
                    //error
                    printf("Your operation expression is wrong!\n");
                    errorTag=1;
                    break;
                    
                default:
                    break;
            }
        }
    }
    if (errorTag==0) {
        if (operands.length!=0) {
            printf("The result is %.4f.\n",pop(&operands));
        }else{
            printf("The result is 0.0.\n");
        }
    }
    return 0;
}
