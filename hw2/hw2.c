
// 1. Insertion sort
// 2. Selection sort
// 3. Quick sort
// 4. Merge sort
// 5. Heap sort



#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 插入排序函式
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i]; // 取出當前要插入的元素
        j = i - 1;

        // 將已排序區域中比 key 大的元素往後移動一個位置
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        // 將 key 放到正確的位置
        arr[j + 1] = key;
    }
}

//Selection sort
void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;

    for (i = 0; i < n - 1; i++) {
        minIdx = i; // 假設當前未排序區域的第一個元素為最小值
        
        // 尋找未排序區域中的最小值索引
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // 將找到的最小值與未排序區域的第一個元素交換
        if (minIdx != i) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}



// 印出陣列的輔助函式
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("請輸入亂數個數：");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("請輸入正整數。\n");
        return 1;
    }

    int arr[n];
    srand(2);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (1000000 - 10000 + 1 ) + 10000;
    }

    printf("隨機產生的數字：\n");
    // printArray(arr, n);

    // insertionSort:每次從未排序區域取出第一個元素，與已排序區域的元素從後往前比較，找到合適的位置後「插入」進去
    printf("insertionSort\n");
    clock_t start = clock();
    insertionSort(arr, n);
    clock_t end = clock();
    double cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU 執行時間：%.6f 秒\n", cpu_time_used);

    // selectionSort:每次從未排序的資料中找出最小值（或最大值），將它放到已排序區域的最後面。
    printf("selectionSort\n");
    start = clock();
    selectionSort(arr, n);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU 執行時間：%.6f 秒\n", cpu_time_used);



    printf("排序後：\n");
    // printArray(arr, n);

    return 0;
}





