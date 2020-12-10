#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int compare(int *arr1, int *arr2, int size){
    for(int i = 0; i < size; i++){
        if(arr1[i] != arr2[i]){
            return 0;
        }
    }
    return 1;
}

void printArray(int *arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *quickSort(int *arr, int size){ 
    if(size < 2){
        return arr;
    }
    else{
        int pivot = arr[0]; 
        int *less = malloc(size * sizeof(int));
        int *greater = malloc(size * sizeof(int));

        int lessSize = 0;
        int greaterSize = 0;

        for(int i = 1; i < size; i++){
            if(arr[i] <= pivot){
                less[lessSize] = arr[i];
                lessSize++;
            }
            else{
                greater[greaterSize] = arr[i];
                greaterSize++;
            }
        }
    
        less = quickSort(less, lessSize);
        greater = quickSort(greater, greaterSize);
        
        for(int i = 0; i < size; i++){
            if(i < lessSize){
                arr[i] = less[i];
            }else if(i == lessSize){
                arr[i] = pivot;
            }else{
                arr[i] = greater[i - lessSize - 1];
            }
        }

        return arr;
    }
}

int main(int argc, char *argv[]) {

//Главное, что работает
    if(argc == 0){
        printf("Time: 0");
        return 0;
    }

    int size = (argc - 1) / 2;

    int *unsortedArray = malloc(size * sizeof(int));
    int *sortedArray = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        unsortedArray[i] =  atoi(argv[i + 1]);
    }

    for(int  i = 0; i < size; i++){
        sortedArray[i] =  strtol(argv[i + size + 1], NULL, 10);
    }

    int isCorrect = compare(quickSort(unsortedArray, size), sortedArray, size);

    if(isCorrect == 1){
        clock_t begin = clock();
        //printf("Begin: %d \n", begin);
        for(int i = 0; i < 900; i++){
            quickSort(unsortedArray, size);
        }
        clock_t end = clock();
        int e = (int)end;
        //printf("End: %d \n", e);
        
        int difference = (int)((int)end - (int)begin);
        printf("%d", difference);
    }else{
        printf("Failed");
    }
    return 0;
}