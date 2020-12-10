#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}

int compare(int *arr1, int *arr2, int size){
    for(int i = 0; i < size; i++){
        if(arr1[i] != arr2[i]){
            return 0;
        }
    }
    return 1;
}


void heapify(int *arr, int size, int i){\
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
        heapify(arr, size, parrent);
    }
}


void heapSort(int *arr, int size){
    for(int i = size / 2 - 1; i > -1; i--){
        heapify(arr, size, i);
    }
    for (int i =  size - 1; i > 0; i--){
        int tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        
        heapify(arr, i, 0);
    }
}

int *introsortLogic(int *arr, int maxDepth, int size){
    if(size <= 1){
        return arr;
    }else if(maxDepth == 0){
        heapSort(arr, size);
        return arr;
    }else{
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
    
        maxDepth--;
        less = introsortLogic(less, maxDepth, lessSize);
        greater = introsortLogic(greater, maxDepth, greaterSize);
        
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

void realSort(int *arr, int size){
    int maxDepth = log(size);
    introsortLogic(arr, maxDepth, size);
}

//I use it in each file to not chang an array
int *sort(int *arr, int size){
    int *localArr = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        localArr[i] = arr[i];
    }
    realSort(localArr, size);
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
        for(int i = 0; i < 900; i++){
            sort(unsortedArray, size);
        }
        clock_t end = clock();
        int e = (int)end;
        
        int difference = (int)((int)end - (int)begin);
        printf("%d", difference);
    }else{
        printf("Failed");
    }
    return 0;
}