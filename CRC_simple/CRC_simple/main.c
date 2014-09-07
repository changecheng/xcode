//
//  main.c
//  CRC_simple
//
//  Created by Change Cheng on 14-8-29.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

#include <stdio.h>

//Convert 16-num to binary, stored in array
const int num=16;
void Hexad2Bin(int x,int binarray[num]){
    
    int i=0;
    int n=0;
    int temp[num];
    for (int i=0; i<num; i++) {
        temp[i]=0;
    }
    do {
        temp[i]=x%2;
        x=x/2;
        i++;
        
    } while (x!=0);    //
    for (; i>0; i--) {
        binarray[n]=temp[i-1];
        n++;
    }
    binarray[n]=-1;
    
}
void Output(int array[num]){
    int i=0;
    
    while (array[i]>=0) {
        printf("%d",array[i]);
        i++;
    }
    printf("\n");
}
//CRC
void CRC(int mx[num],int gx[num],int remain[num]){
    int n1=0;
    int n2=0;
    int i=0;
    while (gx[n1]!=-1) {
        n1++;          //gx has n1 digits
    }
    
    
    while (mx[n2]!=-1) {
        n2++;          //mx has n2 digits
    }
    for (i=0; i<n1-1; i++) {
        mx[n2+i]=0;
    }
    mx[n2+i]=-1;       //mx now has n2+n1-1 digits
    
    //now begin mod2 divide
    int temp[num];
    for (int i=0; i<num; i++) {
        temp[i]=0;
        remain[i]=0;
    }
//    i=n1-1;   //start from n1-1
    i=0;
    int finished=0;
    int temp_first=0;
    int temp_last=0;
    while (1) {

        while ((temp_last-temp_first)<n1) {
            temp[temp_last]=mx[i];
            if (temp[temp_last]==-1) {
                finished=1;
                break;
            }
            temp_last++;
            i++;
            
        }   // until temp has n1 digits
        if (finished==1) {
            break;
        }
        // mod 2 minus
        int g=temp_first;
        for (int j=temp_first; j<temp_last; j++) {
            
            temp[j]=temp[j]^gx[j-g];  //xor
            
        }
      

        
        while (temp[temp_first]!=1 && temp_first<temp_last) {
            temp_first++;
        }  //update temp_first
        
    }
    int j=0;
//    printf("temp_first is %d\n",temp_first);
//    printf("temp_last is %d\n",temp_last);
    
    for (int i=temp_first; i<=temp_last; i++) {
       
        remain[j]=temp[i];
        
        j++;
    }
//    for (int i=0; i<num; i++) {
//        printf("%d",remain[i]);
//        
//    }
//    printf("remain\n");

}


int main(int argc, const char * argv[]) {

    int hexa_g;
    int gx[num];
    int hexa_m;
    int mx[num];
    int remain[num];
    for (int i=0; i<num; i++) {
        gx[i]=0;
        mx[i]=0;
        remain[i]=0;
    }
    printf("Please input your code(hexadecimal without 0x): \n");
    scanf("%x",&hexa_m);
    Hexad2Bin(hexa_m,mx);
    printf("Please input your generator polynominal(hexadecimal without 0x): \n");
    scanf("%x",&hexa_g);
    Hexad2Bin(hexa_g,gx);

    CRC(mx, gx, remain);
    printf("CRC is: \n");
    Output(remain);
    
    return 0;
}
