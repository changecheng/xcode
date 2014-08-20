//
//  main.c
//  Quick_Sort and Binary_Search
//
//  Created by Change Cheng on 14/8/19.
//  Copyright (c) 2014年 Change Cheng. All rights reserved.
//

#include <stdio.h>
//#include <string.h>

//Binary Search//

void BinarySearch(int array[],int m,int n,int item,int *pos){
    int middle=0;
    middle=(m+n)/2;
    if (m<=n) {
        if (item==array[middle]) {
            
            *pos=middle;
        }else if(item<array[middle]){
            BinarySearch(array, m, middle-1, item,pos);
        }else{
            BinarySearch(array, middle+1, n, item,pos);
        }
        
    }
}

//Partition
void Partition(int array[],int m,int n,int *pos){
    int temp=array[m];
    int swapTemp=0;
    int i=m;
    int j=n;
    *pos=m;
    int finished =0;
    while (i<j) {              //i>j,finished
        while (array[j]>=temp) {
            j--;  //from n->m,array[j]>=temp
            if (j==i) {
                finished=1;
            }
        }
        if (finished==1) {
            break;             //break outer loop
        }
        //exchange array[j] with array[*pos]
        swapTemp = array[*pos];
        array[*pos]=array[j];
        array[j]=swapTemp;
        *pos = j;

        while (array[i]<=temp ) {
            i++;                 //from m->n, array[i]<=temp
            if (i==j) {
                finished=1;
            }
        }
        if (finished==1) {
            break;             //break outer loop
        }
        //exchange array[i] with array[*pos]
        swapTemp = array[*pos];
        array[*pos]=array[i];
        array[i]=swapTemp;
        *pos = i;
       
    }
  
    
    
}
//Quick Sort//
void QuickSort(int array[],int m,int n){
    int pos=0;
    if (m<n) {
        Partition(array,m,n,&pos);    //partition based on first item
        QuickSort(array,m,pos-1);
        QuickSort(array,pos+1,n);
    }
    
    
}


int main(int argc, const char * argv[]) {
//    int s1[]={10,9,11,8,7,6,25,30};

//    QuickSort(s1, 0, 7);
//    for (int i=0; i<8; i++) {
//        printf("%d,",s1[i]);
//    }
//    printf("\n");
//
//
//    int n=BinarySearch(s1, 0, 7, 9);
//    if (n>=0){
//        printf("Position is %d.\n",n);
//    }
    
    
//execute
    printf("How many numbers would you like to sort?\n");
    int n=0;
    int array[32];
    scanf("%d",&n);
    printf("Please input %d numbers seperated by space: \n",n);
    
    for (int i=0; i<n; i++) {
        scanf("%d",&array[i]);
    }
    QuickSort(array, 0, n-1);
    printf("The sorted numbers are: \n");
    for (int i=0; i<n; i++) {
        printf("%d,",array[i]);
    }
    printf("\n");
    printf("Please input the number you want to search: \n");
    int sh=0;
    scanf("%d",&sh);
    int pos=0;
//    for (int i=0; i<n; i++) {
//        printf("%d-",array[i]);
//    }                                   //before
    BinarySearch(array, 0, n-1, sh,&pos);
    
//    for (int i=0; i<n; i++) {
//        printf("%d..",array[i]);        //after
//    }
//    printf("pos: %d\n",pos);
    if (pos>=0) {
        printf("Position of your number is: %d\n",pos);
    }else{
        printf("Your number can not be found!!\n");
    }
    
    return 0;
}
