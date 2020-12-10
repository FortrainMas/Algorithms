#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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


void node(int *arr, int size, int i){\
    int parrent = i;
    int rightChild = 2 * i + 2;
    int leftChild = 2 * i + 1;
    
    if(rightChild < size){
        if(arr[parrent] < arr[rightChild]){
            parrent = rightChild;
        }
    }
    
    if(leftChild < size){
        if(arr[parrent] < arr[leftChild]){
            parrent = leftChild;
        }
    }
    
    if(parrent != i){
        int tmp = arr[i];
        arr[i] = arr[parrent];
        arr[parrent] = tmp;
        node(arr, size, parrent);
    }
}


void heapSort(int *arr, int size){
    for(int i = size / 2 - 1; i > -1; i--){
        node(arr, size, i);
    }
    for (int i =  size - 1; i > 0; i--){
        int tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        
        node(arr, i, 0);
    }
}

int *sort(int *arr, int size){
    int *localArr = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        localArr[i] = arr[i];
    }
    heapSort(localArr, size);
    return localArr;
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

    int isCorrect = compare(sort(unsortedArray, size), sortedArray, size);

    if(isCorrect == 1){
        clock_t begin = clock();
        //printf("Begin: %d \n", begin);
        for(int i = 0; i < 900; i++){
            sort(unsortedArray, size);
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
  