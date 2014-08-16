//
//  main.c
//  two-32bit-number-multiply
//
//  Created by Change Cheng on 14/8/15.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

//-9999999999999999999999999999999     //31 ,9

#include <stdio.h>
const int num=32;
const int num2=2*num-1;
const int basenum=10;
void Get32Number();
void Multiply32NumberP();
void Multiply32Number();
void Add64Number2P();
void PrintResult();
int main(int argc, const char * argv[]) {
    int a[num],b[num],c[num2];
    printf("This Program Can Process 2 Numbers(32-digit limited) to Add or Subtract: \n");
    printf("Please input your first number: \n");    //input first num
    Get32Number(a);
    
    printf("Please input your second number: \n");   //input second num
    Get32Number(b);

    Multiply32Number(a, b, c);
    
    printf("The Result is: \n");
    PrintResult(c,num2);
    printf("Hello, World!\n");
    return 0;
}
void Multiply32Number(int a[],int b[],int c[]){
    int s1=a[num-1];
    int s2=b[num-1];
    if (s1==s2) {
        Multiply32NumberP(a, b, c);
        c[num2-1]=0;
    }else{
        Multiply32NumberP(a, b, c);
        c[num2-1]=9;
    }
}
void Get32Number(int temp[num]) {
    
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
            c=c-48;
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
    
}//get a 32-digit number
void Multiply32NumberP(int a[],int b[],int c[]){
    int temp[num2];
    int jinwei[num2];
    for (int i=0; i<num-1; i++) {
        for (int i=0; i<num2; i++) {
            temp[i]=0;
            jinwei[i]=0;
        }//init temp,jinwei
        //b[i]*a -> temp
        int j=0;
        for (j=0; j<num-1; j++) {
            jinwei[j+1]=(b[i]*a[j]+jinwei[j])/basenum;
            temp[j+i]=(b[i]*a[j]+jinwei[j])%basenum;      // store temp
        }
        temp[j+i]=jinwei[j];
        //add temp and c
        Add64Number2P(temp, c, c,num2);
    }
    
}
//add two numbers with (digits) digits
void Add64Number2P(int a[],int b[],int c[],int digits) {
    
    int jinwei[digits];
    for (int i=0; i<digits; i++) {
        jinwei[i]=0;
        
    }
    for (int i = 0 ; i< digits-1; i++) {
        jinwei[i+1] = (a[i]+b[i]+jinwei[i])/basenum;
        c[i]=(a[i]+b[i]+jinwei[i])%basenum;
        
    }

}
//print result
void PrintResult(int c[],int digits){
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

