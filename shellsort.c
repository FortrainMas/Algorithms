#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>




void printArray(int *arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shellSort(int arr[], int size){
    int step = size / 2;
    while(step > 0){
        for(int i = step; i < size; i++){
            for(int j = i - step; j >= 0; j-=step){
                if(arr[j+ step] < arr[j]){
                    swap(&arr[j + step], &arr[j]);
                }
            }
        }
        step /= 2;
    }
}

int *sort(int *arr, int size){
    int *localArr = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        localArr[i] = arr[i];
    }
    shellSort(localArr, size);
    return localArr;
}


int main(int argc, char *argv[]){
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

    struct timeval stop, start;

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