//
//  main.c
//  C language
//
//  Created by Change Cheng on 14-8-11.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

#include <stdio.h>

//999999999999999999999999999999999999999999999999999999999999999
void Get64Number();
void Add64Number2P();
void Sub64Number2P();
void Add64Number();
void Sub64Number();
int Compare64();
void Divide64Number();
void Print64Result();
const int basenum = 10;
const int num = 64;
int main(int argc, const char * argv[]) {
    int a[num],b[num],shang[num],yu[num],c[num+1];
    char operator;
    printf("This Program Can Process 2 Numbers(64-digit limited) to Add or Subtract: \n");
    printf("Please input your first number: \n");    //input first num
    Get64Number(a);
    
    printf("Please input your second number: \n");   //input second num
    Get64Number(b);
    printf("Please choose add or subtract(input + or - or /): \n");//input operand
    scanf("%s",&operator);
    printf("The Result is: \n");
    if (operator=='+') {
        Add64Number(a, b, c);
        Print64Result(c, num+1);
    }else if (operator=='-'){
        Sub64Number(a, b, c);
        Print64Result(c, num+1);
    }else if (operator=='/'){
        Divide64Number(a,b,shang,yu);
        printf("shang: ");
        Print64Result(shang,num);
        printf("yushu: ");
        Print64Result(yu,num);
    }
    return 0;
}
void Get64Number(int temp[num]) {
    
    int jinwei[num];
    for (int i=0; i<num; i++) {
        temp[i] = 0;
        jinwei[i] = 0;
        
    }//init temp,jinwei
    
    int c=0,i=0;
    c=getchar();
    if (c=='-') {
        temp[num-1]=9;
        //has symbol
        while ((c = getchar()) != '\n') {
            c=c-48;  // change char to int
            jinwei[0]=c;
            
            for (i=0; i<num-1; i++) {
                jinwei[i+1]=(temp[i] *10 +jinwei[i])/basenum;
                temp[i]=(temp[i] *10 +jinwei[i])%basenum;
                
            }
        }
    }else {
        do {
            c=c-48;
            jinwei[0]=c;
            
            for (i=0; i<num-1; i++) {
                jinwei[i+1]=(temp[i] *10 +jinwei[i])/basenum;
                temp[i]=(temp[i] *10 +jinwei[i])%basenum;
                
            }
            
        } while ((c = getchar()) != '\n');
    }
}
//2positive numbers add
void Add64Number2P(int a[],int b[],int c[]) {
    
    int jinwei[num+1];
    for (int i=0; i<=num; i++) {
        jinwei[i]=0;
    }//initial
    for (int i = 0 ; i< num-1; i++) {
        jinwei[i+1] = (a[i]+b[i]+jinwei[i])/basenum;
        c[i]=(a[i]+b[i]+jinwei[i])%basenum;
        
    }
    c[num-1]=jinwei[num-1];
}
//2positive numbers minus, result is abs
void Sub64Number2P(int a[],int b[],int c[]) {
    
    int jiewei[num+1];
    for (int i=0; i<=num; i++) {
        jiewei[i]=0;
    }
    int cp =Compare64(a,b);
    if (cp>=0) {
        for (int i = 0 ; i< num-1; i++) {
            if ((a[i]-jiewei[i]-b[i])>=0) {
                c[i]=a[i]-jiewei[i]-b[i];
            }else{
                jiewei[i+1]=1;
                c[i]=a[i]+1*basenum-jiewei[i]-b[i];
                
            }
            
        } //subtract
    }else{
        for (int i = 0 ; i< num-1; i++) {           //a[num-1] symbol
            if ((b[i]-jiewei[i]-a[i])>=0) {
                c[i]=b[i]-jiewei[i]-a[i];
            }else{
                jiewei[i+1]=1;
                c[i]=b[i]+1*basenum-jiewei[i]-a[i];
            }
        } //subtract
    }
}
//compare two number abs
int Compare64(int a[],int b[]){
    int cp=0;
    for (int i=num-2; i>=0; i--) {      //compare from non-symbol
        if ((cp=(a[i]-b[i]))!=0) {
            break;
        }
    }
    return cp;
}//compare two number abs

//add two numbers with symbol
void Add64Number(int a[],int b[],int c[]) {
    int s1=a[num-1];
    int s2=b[num-1];
    if (s1==0) {
        if (s2==0) {
            Add64Number2P(a, b, c);    //s1,s2 p p
        }else{
            
            Sub64Number2P(a, b, c);
            int cp=Compare64(a, b);
            if (cp>=0) {
                c[num]=0;
            }else{
                c[num]=9;
            }
            
        }
    }else{
        if (s2==0) {
            Sub64Number2P(b, a, c);    //s1,s2 n p
            int cp=Compare64(b, a);
            if (cp>=0) {
                c[num]=0;
            }else{
                c[num]=9;
            }
        }else{
            Add64Number2P(a, b, c);     //s1,s2 n,n
            c[num]=9;
        }
    }
}
//subtract two numbers with symbol
void Sub64Number(int a[],int b[],int c[]) {
    int s1=a[num-1];
    int s2=b[num-1];
    if (s1==0) {
        if (s2==0) {
            Sub64Number2P(a, b, c);     //s1,s2 p p
            int cp=Compare64(a, b);
            if (cp>=0) {
                c[num]=0;
            }else{
                c[num]=9;
            }
        }else{
            Add64Number2P(a, b, c);     //s1,s2 p,n
        }
    }else{
        if (s2==0) {
            //s1,s2 n p
            Add64Number2P(a, b, c);
            c[num]=9;
        }else{
            //s1,s2 n,n
            Sub64Number2P(b, a, c);
            int cp=Compare64(b, a);
            if (cp>=0) {
                c[num]=0;
            }else{
                c[num]=9;
            }
            
        }
        
    }
}

//divide two numbers with symbol
void Divide64Number(int a[],int b[],int shang[],int yu[]){
    //initial
    int iszero=0;
    //store symbol
    int s1=a[num-1];
    int s2=b[num-1];
    //divide main func
    int addone[num];
    for (int i=0; i<num-1; i++) {
        shang[i]=0;
        yu[i]=0;
        addone[i] = 0;
    }
    addone[0]=1;   //+1
    //consider 0
    for (int i=num-2; i>=0; i--) {      //compare from non-symbol
        if ((iszero=(b[i]-0))!=0) {
            break;
        }
    }
    if (iszero==0) {
        printf("Error, OverFlow because 0 is divided...\n");     //judge,b==0,overflow
    }else{
        
        int cp=0;
        for (int i=0; i<num-1; i++) {
            yu[i] = a[i];
        }//yu <- a
        while ((cp=Compare64(yu, b))>=0) {
            
            Sub64Number2P(yu, b, yu);               //yu-b
            Add64Number2P(shang, addone, shang);  //shang++
            
        }
        //process symbol
        if (s1==s2) {
            shang[num-1]=0;
        }else{
            //shang < 0
            shang[num-1]=9;
            
        }
        if (s1==9) {
            yu[num-1]=9;      //opr1 < 0 -> yu<0
        }
        
        
    }
    
}

void Print64Result(int c[],int digits){
    //judge whether c == 0
    int iszero=0;
    for (int i=num-2; i>=0; i--) {      //compare from non-symbol
        if ((iszero=(c[i]-0))!=0) {
            break;
        }
    }
    if (iszero==0) {
        printf("0\n");    //print 0 if c==0
    }else{
        int i=digits;
        if (c[digits-1]==9) {
            printf("-");
        }
        for ( i=digits-2; i>0 && c[i]==0; i--) {
            ;    //skip those 0s
        }
        while (i>=0) {
            printf("%d",c[i]);
            i--;
        }
        printf("\n");
    }
}
